module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.RasterizerStage;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
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
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class RasterizerStage
	{
	public:

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
			_rasterizer = RasterizerFactory::create(_inputAssemblerStage->primitiveTopology(), _state);
		}

		void execute(const PrimitiveStream& primitiveStream)
		{
			for (auto& primitive : primitiveStream)
			{
				// frustum culling
				// Clipping
				// Perspective divide (homogeneous division)
				// Backface culling (face culling)
				// Transform from clip space tp screen space (viewport transformation)

				_rasterizer->rasterize(primitive);
			}
			

			/*
			
			// TODO: Allow selection of different viewport.
		    var viewport = _viewports[0];

		    var outputInputBindings = ShaderOutputInputBindings.FromShaderSignatures(
		        previousStageOutputSignature, pixelShader);

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

		void drawLine(const Point2i& p0, const Point2i& p1, const Color& color, Texture& target)
		{
			bool steep = false;

			auto x0 = p0.x();
			auto y0 = p0.y();
			auto x1 = p1.x();
			auto y1 = p1.y();

			if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
				std::swap(x0, y0);
				std::swap(x1, y1);
				steep = true;
			}
			if (x0 > x1) {
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			int dx = x1 - x0;
			int dy = y1 - y0;
			int derror2 = std::abs(dy) * 2;
			int error2 = 0;
			int y = y0;
			for (int x = x0; x <= x1; x++) {
				if (steep) {
					target.at(y, x) = color;
				}
				else {
					target.at(x, y) = color;
				}
				error2 += derror2;
				if (error2 > dx) {
					y += (y1 > y0 ? 1 : -1);
					error2 -= dx * 2;
				}
			}
		}

	private:

		RasterizerState _state;
		std::unique_ptr<Rasterizer> _rasterizer;
		std::shared_ptr<InputAssemblerStage> _inputAssemblerStage;
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
