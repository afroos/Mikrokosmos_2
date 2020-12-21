module;

#include <iostream>
#include <memory>

export module Mikrokosmos.Graphics.Rendering.DeviceContext;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.InputAssemblerStage;
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
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexShaderStage;
import Mikrokosmos.Graphics.Rendering.VertexStream;
import Mikrokosmos.Graphics.Rendering.Viewport;

export namespace mk
{
	class DeviceContext
	{
	public:

		DeviceContext()
		{
			_inputAssemblerStage = std::make_shared<InputAssemblerStage>();
			_vertexShaderStage = std::make_shared<VertexShader>();
			_rasterizerStage = std::make_shared<RasterizerStage>(_inputAssemblerStage);
			_pixelShader = std::make_shared<PixelShader>();
			_outputMergerStage = std::make_shared<OutputMergerStage>();
		}

		std::shared_ptr<InputAssemblerStage> inputAssemblerStage() { return _inputAssemblerStage; }
		
		std::shared_ptr<VertexShader> vertexShader() { return _vertexShaderStage; }
		
		std::shared_ptr<RasterizerStage> rasterizerStage() { return _rasterizerStage; }
		
		std::shared_ptr<PixelShader> pixelShader() { return _pixelShader; }
		
		std::shared_ptr<OutputMergerStage> outputMergerStage() { return _outputMergerStage; }

		void drawIndexed(std::size_t indexCount, std::size_t startIndexLocation, std::size_t baseVertexLocation)
		{
			auto vertexStream = _inputAssemblerStage->generateVertexStreamIndexed(indexCount, startIndexLocation, baseVertexLocation);
			drawInternal(vertexStream);
		}



	private:

		void drawInternal(const VertexStream& vertexStream)
		{
			auto processedVertexStream = _vertexShaderStage->process(vertexStream);
			
			auto primitiveStream = _inputAssemblerStage->generatePrimitiveStream(processedVertexStream);
			
			auto fragmentStream = _rasterizerStage->process(primitiveStream);
			
			//_pixelShaderStage->process(fragmentStream);
			
			_outputMergerStage->process(fragmentStream);

		}

		std::shared_ptr<InputAssemblerStage> _inputAssemblerStage;
		std::shared_ptr<VertexShader> _vertexShaderStage;
		std::shared_ptr<RasterizerStage> _rasterizerStage;
		std::shared_ptr<PixelShader> _pixelShader;
		std::shared_ptr<OutputMergerStage> _outputMergerStage;

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