module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.Engine;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Device;
import Mikrokosmos.Graphics.Rendering.DeviceContext;
import Mikrokosmos.Graphics.Rendering.Effect;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.InputAssemblerStage;
import Mikrokosmos.Graphics.Rendering.Mesh;
import Mikrokosmos.Graphics.Rendering.OutputMerger;
import Mikrokosmos.Graphics.Rendering.PixelShader;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.PrimitiveStream;
import Mikrokosmos.Graphics.Rendering.PrimitiveTopology;
import Mikrokosmos.Graphics.Rendering.Rasterizer;
import Mikrokosmos.Graphics.Rendering.RasterizerFactory;
import Mikrokosmos.Graphics.Rendering.RasterizerStage;
import Mikrokosmos.Graphics.Rendering.RasterizerState;
import Mikrokosmos.Graphics.Rendering.RenderTargetView;
import Mikrokosmos.Graphics.Rendering.SwapChain;
import Mikrokosmos.Graphics.Rendering.SwapChainPresenter;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexShaderStage;
import Mikrokosmos.Graphics.Rendering.VertexStream;
import Mikrokosmos.Graphics.Rendering.Viewport;

export namespace mk
{
	class Engine
	{
	public:

		Engine()
		{
			_device = std::make_shared<Device>();
			_immediateContext = _device->immediateContext();
		}

		std::shared_ptr<VertexBuffer> createVertexBuffer(std::size_t size)
		{
			return _device->createVertexBuffer(size);
		}

		std::shared_ptr<IndexBuffer> createIndexBuffer(std::size_t size)
		{
			return _device->createIndexBuffer(size);
		}



		void clearBuffers()
		{

		}

		void draw(const std::shared_ptr<Mesh>& mesh)
		{

		}

	private:

		std::shared_ptr<Device> _device;
		std::shared_ptr<DeviceContext> _immediateContext;
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