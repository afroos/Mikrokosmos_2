#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <memory>
#include <string>

import Mikrokosmos.Applications;
import Mikrokosmos.Graphics;

class BasicTriangleApplication final : public mk::WindowApplication
{
public:

    BasicTriangleApplication()
		:
        mk::WindowApplication{ "Basic Triangle", 800, 600 }
	{

	}

private:

	void initialize() noexcept override
	{
        _presenter = std::make_shared<mk::SFMLSwapChainPresenter>(_window);

        _device = std::make_shared<mk::Device>();

        _swapChain = _device->createSwapChain(windowWidth(), windowHeight(), _presenter.get());

        _renderTargetView = _device->createRenderTargetView(&_swapChain->backBuffer());

        _context = _device->immediateContext();

        mk::Vertex vertexes[] =
        {
            { {+0.0f, +0.5f, +0.0f}, mk::Color::Red()   },
            { {+0.5f, -0.5f, +0.0f}, mk::Color::Green() },
            { {-0.5f, -0.5f, +0.0f}, mk::Color::Blue()  }
        }; 

        auto vertexBuffer = _device->createVertexBuffer(vertexes);

        mk::Index indexes[] = {0, 1, 2};

        auto indexBuffer = _device->createIndexBuffer(indexes);

        _context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::TriangleList);
        _context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
        _context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

        _context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Solid });
        _context->rasterizerStage()->setViewport({ 0.0f, 0.0f, (float) windowWidth(), (float) windowHeight() });

        _context->outputMergerStage()->setRenderTargetView(*_renderTargetView);
	}

    void render() noexcept override
    {
        _renderTargetView->clear(mk::Color{ 0.0f, 0.2f, 0.4f, 1.0f });
        _context->drawIndexed(3, 0, 0);
        _swapChain->present();
    }

private:

    std::shared_ptr<mk::SFMLSwapChainPresenter> _presenter;
    std::shared_ptr<mk::Device> _device;
    std::shared_ptr<mk::SwapChain> _swapChain;
    std::shared_ptr<mk::RenderTargetView> _renderTargetView;
    std::shared_ptr<mk::DeviceContext> _context;
};

int main() 
{
    BasicTriangleApplication application;

    try 
    {
        application.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}