#include <cstdint>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <span>
#include <string>

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics;
import Mikrokosmos.Graphics.Rendering.SFMLSwapChainPresenter;
import Mikrokosmos.Mathematics.Algebra;

int main()
{
    auto width = 640;
    auto height = 480;

    auto device = std::make_shared<mk::Device>();

    sf::RenderWindow window(sf::VideoMode(width, height), "Hello Triangle");

    auto presenter = std::make_shared<mk::SFMLSwapChainPresenter>(window);

    auto swapChain = device->createSwapChain(width, height, presenter.get());

    //auto target = std::make_shared<mk::Texture2D>(height, width);
    //target->fill(mk::Color{ 100, 149, 237 });
    
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

    //auto vertexShader = device->createVertexShader(...);

    //auto effect = std::make_shared<mk::Effect>();
   
    //auto triangle = std::make_shared<mk::Mesh>(vertexBuffer, indexBuffer, effect);

    //context->vertexShaderStage()->setShader(vertexShader);

    context->rasterizerStage()->setState(mk::RasterizerState{.fillMode = mk::FillMode::Wireframe});
    context->rasterizerStage()->setViewport({ 0.0, 0.0, (float) width, (float) height });

    //context->pixelShaderStage()->setShader(pixelShader);

    context->outputMergerStage()->setRenderTargetView(*renderTargetView);

    //mk::RasterizerStage rasterizer{ context->inputAssemblerStage() };

    //rasterizer.drawLine(mk::Point2i{ 13, 20 }, mk::Point2i{ 80, 40 }, mk::Color::White(), *target);
    //rasterizer.drawLine(mk::Point2i{ 20, 13 }, mk::Point2i{ 40, 80 }, mk::Color::Red(), *target);
    //rasterizer.drawLine(mk::Point2i{ 80, 40 }, mk::Point2i{ 13, 20 }, mk::Color::Red(), *target);


    context->drawIndexed(indexBuffer->size(), 0, 0);

   

    //auto pixelData = reinterpret_cast<uint8_t*>(target->data());

    //sf::Image imag|e;
    //image.create(width, height, pixelData);

    //image.flipVertically();

    //sf::Texture texture;
    //texture.loadFromImage(image);

    //sf::Sprite sprite(texture);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        swapChain->present();
        //window.clear();
        //window.draw(sprite);
        //window.display();
    }

    return 0;
}