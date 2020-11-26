module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.DeviceContext;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.InputAssembler;
import Mikrokosmos.Graphics.Rendering.OutputMerger;
import Mikrokosmos.Graphics.Rendering.PixelShader;
import Mikrokosmos.Graphics.Rendering.Rasterizer;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexShader;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{
	class DeviceContext
	{
	public:

		DeviceContext()
		{
			inputAssembler_ = std::make_shared<InputAssembler>();
			vertexShader_ = std::make_shared<VertexShader>();
			rasterizer_ = std::make_shared<Rasterizer>();
			pixelShader_ = std::make_shared<PixelShader>();
			outputMerger_ = std::make_shared<OutputMerger>();
		}

		std::shared_ptr<InputAssembler> inputAssembler() { return inputAssembler_; }
		std::shared_ptr<VertexShader> vertexShader() { return vertexShader_; }
		std::shared_ptr<Rasterizer> rasterizer() { return rasterizer_; }
		std::shared_ptr<PixelShader> pixelShader() { return pixelShader_; }
		std::shared_ptr<OutputMerger> outputMerger() { return outputMerger_; }

		void drawIndexed(std::size_t indexCount, std::size_t startIndexLocation, std::size_t baseVertexLocation)
		{
			drawInternal(inputAssembler_->generateVertexStreamIndexed(indexCount, startIndexLocation, baseVertexLocation));
		}



	private:

		void drawInternal(const VertexStream& vertexStream)
		{
			/*
			
			var vertexShaderOutputs = _vertexShader.Execute(vertexStream);
			var primitiveStream = _inputAssembler.GetPrimitiveStream(vertexShaderOutputs);

			IEnumerable<InputAssemblerPrimitiveOutput> rasterizerInputs;
			PrimitiveTopology rasterizerInputTopology;
			OutputSignatureChunk rasterizerInputSignature;
			if (_geometryShader.IsActive)
			{
				rasterizerInputs = _geometryShader.Execute(primitiveStream, _inputAssembler.PrimitiveTopology);
				rasterizerInputTopology = _geometryShader.OutputTopology;
				rasterizerInputSignature = _geometryShader.Shader.Bytecode.OutputSignature;
			}
			else
			{
				rasterizerInputs = primitiveStream;
				rasterizerInputTopology = _inputAssembler.PrimitiveTopology;
				rasterizerInputSignature = _vertexShader.Shader.Bytecode.OutputSignature;
			}

			var rasterizerOutputs = _rasterizer.Execute(rasterizerInputs, rasterizerInputTopology,
				rasterizerInputSignature, _pixelShader.Shader.Bytecode,
				_outputMerger.MultiSampleCount);

			var pixelShaderOutputs = _pixelShader.Execute(rasterizerOutputs);
			_outputMerger.Execute(pixelShaderOutputs);

			*/
		}

		std::shared_ptr<InputAssembler> inputAssembler_;
		std::shared_ptr<VertexShader> vertexShader_;
		std::shared_ptr<Rasterizer> rasterizer_;
		std::shared_ptr<PixelShader> pixelShader_;
		std::shared_ptr<OutputMerger> outputMerger_;

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