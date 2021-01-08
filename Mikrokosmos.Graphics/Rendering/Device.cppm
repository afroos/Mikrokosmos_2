module;

#include <functional>
#include <map>
#include <memory>
#include <span>
#include <string>
#include <string_view>

export module Mikrokosmos.Graphics.Rendering.Device;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.DeviceContext;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentShader;
import Mikrokosmos.Graphics.Rendering.FragmentShaderStage;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.InputAssemblerStage;
import Mikrokosmos.Graphics.Rendering.OutputMerger;
import Mikrokosmos.Graphics.Rendering.Pixel;
import Mikrokosmos.Graphics.Rendering.PixelStream;
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
import Mikrokosmos.Graphics.Rendering.VertexShader;
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

		std::shared_ptr<VertexShader> createVertexShader(std::string_view type)
		{
			static std::map<
				std::string,
				std::function<std::shared_ptr<VertexShader>()>> dispatchTable
			{
				{ "",        []() { return std::make_shared<VertexShader>();      } },
				{ "Basic",   []() { return std::make_shared<BasicVertexShader>(); } }
			};

			auto it = dispatchTable.find(type.data());
			if (it != dispatchTable.end()) return it->second();
			else return nullptr;
		}

		std::shared_ptr<FragmentShader> createFragmentShader(std::string_view type)
		{
			static std::map<
				std::string,
				std::function<std::shared_ptr<FragmentShader>()>> dispatchTable
			{
				{ "",        []() { return std::make_shared<FragmentShader>();      } },
				{ "Basic",   []() { return std::make_shared<BasicFragmentShader>(); } }
			};

			auto it = dispatchTable.find(type.data());
			if (it != dispatchTable.end()) return it->second();
			else return nullptr;
		}

	private:

		std::shared_ptr<DeviceContext> _immediateContext;

	};
}