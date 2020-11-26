module;

#include <cstddef>
#include <memory>

export module Mikrokosmos.Graphics.Rendering.InputAssembler;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
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

		std::shared_ptr<VertexBuffer> vertexBuffer() const { return vertexBuffer_; }
		
		std::shared_ptr<IndexBuffer> indexBuffer() const { return indexBuffer_; }
		
		PrimitiveTopology primitiveTopology() const { return primitiveTopology_; }

		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
		{
			vertexBuffer_ = vertexBuffer;
		}

		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			indexBuffer_ = indexBuffer;
		}

		void setPrimitiveTopology(PrimitiveTopology primitiveTopology) 
		{ 
			primitiveTopology_ = primitiveTopology; 
		}

		VertexStream generateVertexStreamIndexed(std::size_t indexCount, std::size_t startIndexLocation, std::size_t baseVertexLocation)
		{
			return VertexStream{ indexCount, indexBuffer_->data() + startIndexLocation, vertexBuffer_->data() };
		}

	private:

		std::shared_ptr<VertexBuffer> vertexBuffer_;
		std::shared_ptr<IndexBuffer> indexBuffer_;
		PrimitiveTopology primitiveTopology_;

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