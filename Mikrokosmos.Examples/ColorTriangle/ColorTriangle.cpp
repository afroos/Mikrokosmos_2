#include <string>

import Mikrokosmos.Applications.WindowApplication;
//import Mikrokosmos.Containers;
import Mikrokosmos.Graphics;

class ColorTriangle : public mk::WindowApplication
{
public:

	ColorTriangle()
		:
        mk::WindowApplication{ {.name = "Color Triangle", .windowSize = {800, 600}} }
	{

	}

	void initialize() noexcept override
	{
        auto width = 800;
        auto height = 800;

        sf::RenderWindow window(sf::VideoMode(width, height), "Hello Triangle");

        auto presenter = std::make_shared<mk::SFMLSwapChainPresenter>(window);

        auto swapChain = device->createSwapChain(width, height, presenter.get());

        auto renderTargetView = device->createRenderTargetView(&swapChain->backBuffer());

        auto context = device->immediateContext();

        mk::Vertex vertexes[] =
        {
            { {-0.5f, -0.5f, +0.0f}, mk::Color::Red()   },
            { {+0.5f, -0.5f, +0.0f}, mk::Color::Green() },
            { {+0.0f, +0.5f, +0.0f}, mk::Color::Blue()  }
        };

        auto vertexBuffer = device->createVertexBuffer(vertexes);

         mk::Index indexes[] = {0, 1, 2};

        auto indexBuffer = device->createIndexBuffer(indexes);

        context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::TriangleList);
        context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
        context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

            auto vertexShader = device->createVertexShader("");

            context->vertexShaderStage()->setShader(vertexShader);

        context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Solid });
        context->rasterizerStage()->setViewport({ 0.0, 0.0, (float)width, (float)height });

        auto fragmentShader = device->createFragmentShader("");

            context->fragmentShaderStage()->setShader(fragmentShader);

            context->outputMergerStage()->setRenderTargetView(*renderTargetView);
	}

    void draw() noexcept override
    {
        renderTargetView->clear(mk::Color::Black());
        context->drawIndexed(indexBuffer->size(), 0, 0);
        swapChain->present();
    }

private:



};


int main()
{
	ColorTriangle application;
	return application.run();
}