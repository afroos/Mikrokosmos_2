module;

#include <memory>
#include <span>

export module Mikrokosmos.Graphics.Rendering.Device;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.DeviceContext;
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
import Mikrokosmos.Graphics.Rendering.SwapChain;
import Mikrokosmos.Graphics.Rendering.SwapChainPresenter;
import Mikrokosmos.Graphics.Rendering.Texture;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexShaderStage;
import Mikrokosmos.Graphics.Rendering.VertexStream;
import Mikrokosmos.Graphics.Rendering.Viewport;

export namespace mk
{
	class Device
	{
	public:

		Device()
		{
			_immediateContext = std::make_shared<DeviceContext>();
		}

		std::shared_ptr<DeviceContext> immediateContext()
		{
			return _immediateContext;
		}

		std::shared_ptr<VertexBuffer> createVertexBuffer(std::size_t size)
		{
			return std::make_shared<VertexBuffer>(size);
		}

		std::shared_ptr<VertexBuffer> createVertexBuffer(std::span<Vertex> vertexes)
		{
			return std::make_shared<VertexBuffer>(vertexes);
		}

		std::shared_ptr<IndexBuffer> createIndexBuffer(std::size_t size)
		{
			return std::make_shared<IndexBuffer>(size);
		}

		std::shared_ptr<IndexBuffer> createIndexBuffer(std::span<Index> indexes)
		{
			return std::make_shared<IndexBuffer>(indexes);
		}

		std::shared_ptr<SwapChain> createSwapChain(std::size_t width, std::size_t height, SwapChainPresenter* presenter)
		{
			return std::make_shared<SwapChain>(width, height, presenter);
		}

		std::shared_ptr<RenderTargetView> createRenderTargetView(Texture2D* resource)
		{
			return std::make_shared<RenderTargetView>(resource);
		}

	private:

		std::shared_ptr<DeviceContext> _immediateContext;

	};
}