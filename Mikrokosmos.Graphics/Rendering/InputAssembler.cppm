module;

#include <cstddef>
#include <memory>
#include <span>

export module Mikrokosmos.Graphics.Rendering.InputAssembler;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.PrimitiveStream;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{

	enum class PrimitiveTopology
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};

	class InputAssembler
	{
	public:

		InputAssembler() = default;

		std::shared_ptr<VertexBuffer> vertexBuffer() const { return _vertexBuffer; }
		
		std::shared_ptr<IndexBuffer> indexBuffer() const { return _indexBuffer; }
		
		PrimitiveTopology primitiveTopology() const { return _primitiveTopology; }

		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
		{
			_vertexBuffer = vertexBuffer;
		}

		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			_indexBuffer = indexBuffer;
		}

		void setPrimitiveTopology(PrimitiveTopology primitiveTopology) 
		{ 
			_primitiveTopology = primitiveTopology; 

			switch (_primitiveTopology)
			{
			case mk::PrimitiveTopology::PointList:
				_primitiveSize = 1;
				_primitiveAssemblyStep = 1;
				break;
			case mk::PrimitiveTopology::LineList:
				_primitiveSize = 2;
				_primitiveAssemblyStep = 2;
				break;
			case mk::PrimitiveTopology::LineStrip:
				_primitiveSize = 2;
				_primitiveAssemblyStep = 1;
				break;
			case mk::PrimitiveTopology::TriangleList:
				_primitiveSize = 3;
				_primitiveAssemblyStep = 3;
				break;
			case mk::PrimitiveTopology::TriangleStrip:
				_primitiveSize = 3;
				_primitiveAssemblyStep = 1;
				break;
			default:
				_primitiveSize = 0;
				_primitiveAssemblyStep = 0;
			}
		}

		VertexStream generateVertexStreamIndexed(std::size_t indexCount, std::size_t startIndexLocation, std::size_t baseVertexLocation)
		{		
			return VertexStream{ *_vertexBuffer, *_indexBuffer, indexCount, startIndexLocation, baseVertexLocation };
		}

		PrimitiveStream generatePrimitiveStream(const VertexStream& vertexStream)
		{
			auto primitiveCount = vertexStream.size() / _primitiveSize;
			auto currentVertex = vertexStream.begin();

			PrimitiveStream primitiveStream(primitiveCount);
			
			std::size_t offset = 0;
			for (auto& primitive : primitiveStream)
			{
				auto vertexList = vertexStream.slice(offset, _primitiveSize);
				primitive = Primitive{ vertexList.begin(), vertexList.end() };
				offset += _primitiveAssemblyStep;
			}

			/*switch (_primitiveTopology)
			{
			case PrimitiveTopology::PointList:
				while (currentVertex != vertexStream.end())
				{
					//auto vertex0 = currentVertex;
					//Primitive primitive{ {vertex0} };
					//primitiveStream.add(primitive);
					//++currentVertex;
				}
				break;

			case PrimitiveTopology::LineList:
				while (currentVertex != vertexStream.end())
				{
					//auto vertex0 = currentVertex;
					//++currentVertex;
					//auto vertex1 = currentVertex;
					//Primitive line(vertex0, vertex1);
					//primitiveStream.add(line);
					//++currentVertex;
				}
				break;

			case PrimitiveTopology::LineStrip:
				break;

			case PrimitiveTopology::TriangleList:
				while (currentVertex != vertexStream.end())
				{
					//auto vertex0 = currentVertex;
					//++currentVertex;
					//auto vertex1 = currentVertex;
					//++currentVertex;
					//auto vertex2 = currentVertex;
					//auto vertexes = { vertex0, vertex1, vertex2 };
					//Primitive primitive{ 3 , vertexes };
					//primitiveStream.add(primitive);
					//++currentVertex;
				}
				break;

			case PrimitiveTopology::TriangleStrip:
				break;

			default:
				break;
			}
			//for (auto vertex : vertexStream)
			//{

			//}*/
			

			return primitiveStream;
		}

	private:

		std::shared_ptr<VertexBuffer> _vertexBuffer;
		std::shared_ptr<IndexBuffer> _indexBuffer;
		PrimitiveTopology _primitiveTopology;
		std::size_t _primitiveSize;
		std::size_t _primitiveAssemblyStep;
	};
}

/*
Input Assembler
	*Input layout
	1 or more vertex buffers
	0 or 1 index buffer
	*index buffer format (16-bit or 32-bit)
	primitive topology setting

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

// Vertex specification
// Vertex shader
// Primitive assembly
// Clipping
// Viewport transformation
// Backface culling
// Rasterization
// Fragment shader
// Framebuffer processing