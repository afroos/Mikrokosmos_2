module;

#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>

export module Mikrokosmos.Graphics.Rendering.RasterizerStage;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.InputAssemblerStage;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.PrimitiveStream;
import Mikrokosmos.Graphics.Rendering.PrimitiveTopology;
import Mikrokosmos.Graphics.Rendering.Rasterizer;
import Mikrokosmos.Graphics.Rendering.RasterizerFactory;
import Mikrokosmos.Graphics.Rendering.RasterizerState;
import Mikrokosmos.Graphics.Rendering.Texture;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexStream;
import Mikrokosmos.Graphics.Rendering.Viewport;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class RasterizerStage
	{
	public:

		RasterizerStage() = delete;

		RasterizerStage(std::shared_ptr<InputAssemblerStage> inputAssemblerStage)
			:
			_inputAssemblerStage{ inputAssemblerStage }
		{
		}

		RasterizerState state() const
		{
			return _state;
		}

		void setState(const RasterizerState& state)
		{
			_state = state;
			_rasterizer = std::move(RasterizerFactory::create(_inputAssemblerStage->primitiveTopology(), _state));
		}

		void setViewport(const Viewport& viewport)
		{
			_viewport = viewport;
		}

		FragmentStream process(const PrimitiveStream& primitiveStream)
		{

			FragmentStream fragmentStream;
			fragmentStream.reserve(static_cast<std::size_t>(_viewport.width() * _viewport.height()));

			auto vertexCount = primitiveStream[0].vertexCount();

			std::vector<Vertex> vertexes{ vertexCount };

			for (auto& primitive : primitiveStream)
			{
				for (std::size_t i = 0; i < vertexCount; i++)
				{
					vertexes[i] = primitive.vertex(i);
				}
				
				// Frustum culling.

				// Frustum clipping.
				auto clipped = false;
				for (auto& vertex : vertexes)
				{
					const auto& position = vertex.position();
					const auto absW = std::abs(position.w());

					if (position.x() < -position.w() || position.x() > position.w() ||
						position.y() < -position.w() || position.y() > position.w() ||
						position.z() < -position.w() || position.z() > position.w())
					{
						clipped = true;
						break;
					}
				}
				if (clipped) continue;

				// Perspective divide (clip space to NDC space).
				for (auto& vertex : vertexes)
				{
					auto& position = vertex.position();
					position.x() /= position.w();
					position.y() /= position.w();
					position.z() /= position.w();
				}

				// Face culling.
				if (vertexCount > 2)
				{
					Vector3f a{ vertexes[0].position() };
					Vector3f b{ vertexes[1].position() };
					Vector3f c{ vertexes[2].position() };

					auto ab = b - a;
					auto ac = c - a;

					auto normal = cross(ab, ac);

					auto faceIsCounterClockwise = (normal.z() > 0.0f);

					if (faceIsCounterClockwise == _state.frontCounterClockwise && _state.cullMode == CullMode::Front   
					    || faceIsCounterClockwise != _state.frontCounterClockwise && _state.cullMode == CullMode::Back) continue;
				}

				// Viewport transformation (NDC space to screen space).
				for (auto& vertex : vertexes)
				{
					auto& position = vertex.position();
					position.x() = (position.x() + 1.0f) * _viewport.width()  * 0.5f + _viewport.x();
					position.y() = (1.0f - position.y()) * _viewport.height() * 0.5f + _viewport.y();
					position.z() = _viewport.minDepth() + position.z() * (_viewport.maxDepth() - _viewport.minDepth());
				}

				_rasterizer->rasterize(vertexes, fragmentStream);

			}
			return fragmentStream;

			/*
			
			// TODO: Allow selection of different viewport.
		    var viewport = _viewports[0];

		    var outputInputBindings = ShaderOutputInputBindings.FromShaderSignatures(
		        previousStageOutputSignature, fragmentShader);

			var rasterizer = PrimitiveRasterizerFactory.CreateRasterizer(
                primitiveTopology, State.Description, multiSampleCount,
                outputInputBindings, ref viewport, FragmentFilter);

            foreach (var primitive in inputs)
			{
                // Frustum culling.
			    if (ViewportCuller.ShouldCullTriangle(primitive.Vertices))
			        continue;

                // TODO: Clipping.
                // http://simonstechblog.blogspot.tw/2012/04/software-rasterizer-part-2.html#softwareRasterizerDemo

                // Perspective divide.
			    for (int i = 0; i < primitive.Vertices.Length; i++)
			        PerspectiveDivide(ref primitive.Vertices[i].Position);

			    // Backface culling.
			    if (State.Description.CullMode != CullMode.None && rasterizer.ShouldCull(primitive.Vertices))
			        continue;

                // Transform from clip space to screen space.
			    for (int i = 0; i < primitive.Vertices.Length; i++)
                    viewport.MapClipSpaceToScreenSpace(ref primitive.Vertices[i].Position);

                // Rasterize.
				foreach (var fragmentQuad in rasterizer.Rasterize(primitive))
					yield return fragmentQuad;
			}

			
			*/
		}

	private:

		RasterizerState _state;
		std::unique_ptr<Rasterizer> _rasterizer;
		std::shared_ptr<InputAssemblerStage> _inputAssemblerStage;
		Viewport _viewport { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	};
}

/*
Vertex Shader
	Vertex shader program
	up to 16 constant buffers
	up to 128 textures (shader resource view + texture resource)
	*up to 16 samplers (ID3D11SamplerState)

Rasterizer
	rasterizer state (ID3D11RasterizerState)
	up to 16 viewports
	up to 16 scissor rectangles
	
Pixel Shader
	Pixel shader program
	up to 16 constant buffers
	up to 128 textures (shader resource view + texture resource)
	up to 16 samplers (ID3D11SamplerState)
	
Output Merger

	blend state (ID3D11BlendState)
	depth/stencil state (ID3D11DepthStencilState)
	up to 8 render targets (render target resource view + texture resource)

	So to draw anything, you have to set all this state before you call Draw or DrawIndexed.

*/

/*
			Vertex processing
				Vertex shader
			Primitive processing
				Primitive assembly
				Viewport transformation
				Clipping
			Rasterization
				Rasterization
				Face culling
			Fragment processing
				Tests
				Fragment shader
			Pixel processing
				Blend
				Depth
				Stencil
*/
