#include <memory>
#include <string>

import Mikrokosmos.Applications;
import Mikrokosmos.Graphics;

class TriangleExample : public mk::WindowApplication
{
public:

    std::shared_ptr<mk::SFMLSwapChainPresenter> presenter;
    std::shared_ptr<mk::Device> device;
    std::shared_ptr<mk::SwapChain> swapChain;
    std::shared_ptr<mk::RenderTargetView> renderTargetView;
    std::shared_ptr<mk::DeviceContext> context;

    TriangleExample()
		:
        mk::WindowApplication{ {.name = "Color Triangle", .windowSize = {800, 600}} }
	{

	}

	void initialize() noexcept override
	{

        presenter = std::make_shared<mk::SFMLSwapChainPresenter>(_window);

        device = std::make_shared<mk::Device>();

        swapChain = device->createSwapChain(_width, _height, presenter.get());

        renderTargetView = device->createRenderTargetView(&swapChain->backBuffer());

        context = device->immediateContext();

        mk::Vertex vertexes[] =
        {
            { {+0.0f, +0.5f, +0.0f}, mk::Color::Red()   },
            { {+0.5f, -0.5f, +0.0f}, mk::Color::Green() },
            { {-0.5f, -0.5f, +0.0f}, mk::Color::Blue()  }
        }; 

        auto vertexBuffer = device->createVertexBuffer(vertexes);

        mk::Index indexes[] = {0, 1, 2};

        auto indexBuffer = device->createIndexBuffer(indexes);

        context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::TriangleList);
        context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
        context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

        auto vertexShader = device->createVertexShader("");

        context->vertexShaderStage()->setShader(vertexShader);

        context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Solid, 
                                                                  .cullMode = mk::CullMode::None, 
                                                                  .frontCounterClockwise = false });

        context->rasterizerStage()->setViewport({ 0.0, 0.0, (float)_width, (float)_height });

        auto fragmentShader = device->createFragmentShader("");

        context->fragmentShaderStage()->setShader(fragmentShader);

        context->outputMergerStage()->setRenderTargetView(*renderTargetView);
	}

    void draw() noexcept override
    {
        renderTargetView->clear(mk::Color{ 0.0f, 0.2f, 0.4f, 1.0f });
        context->drawIndexed(3, 0, 0);
        swapChain->present();
    }
};

int main()
{
    TriangleExample application;
	return application.run();
}