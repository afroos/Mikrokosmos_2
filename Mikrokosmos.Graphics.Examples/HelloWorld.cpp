#include <cstdint>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <span>
#include <string>

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics;
import Mikrokosmos.Mathematics.Algebra;

int main()
{
    auto width = 640;
    auto height = 480;

    auto device = std::make_shared<mk::Device>();
    auto context = device->immediateContext();

    auto vertexBuffer = device->createVertexBuffer(4);
    vertexBuffer->at(0) = mk::Vertex{ mk::Point3f{1.5f, 2.22f, -5.0f}, mk::Color::Red() };
    vertexBuffer->at(1) = mk::Vertex{ mk::Point3f{1.6f, 2.22f, -5.0f}, mk::Color::Green() };
    vertexBuffer->at(2) = mk::Vertex{ mk::Point3f{1.7f, 2.22f, -5.0f}, mk::Color::Blue() };
    vertexBuffer->at(3) = mk::Vertex{ mk::Point3f{1.8f, 2.22f, -5.0f}, mk::Color::Yellow() };

    auto indexBuffer = device->createIndexBuffer(4);
    indexBuffer->at(0) = 0;
    indexBuffer->at(1) = 1;
    indexBuffer->at(2) = 2;
    indexBuffer->at(3) = 3;

    // auto vertexShader = device->createVertexShader(...);

    //auto effect = std::make_shared<mk::Effect>();
   
    //auto triangle = std::make_shared<mk::Mesh>(vertexBuffer, indexBuffer, effect);

    context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::LineList);
    context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
    context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

    context->rasterizerStage()->setState(mk::RasterizerState{.fillMode = mk::FillMode::Wireframe});

    //context->vertexShader()->setShader(vertexShader);
    //context->pixelShader()->setShader(pixelShader);

    auto target = std::make_shared<mk::Texture>(height, width);
    target->fill(mk::Color{ 100, 149, 237 });

    mk::RasterizerStage rasterizer{ context->inputAssemblerStage() };

    rasterizer.drawLine(mk::Point2i{ 13, 20 }, mk::Point2i{ 80, 40 }, mk::Color::White(), *target);
    rasterizer.drawLine(mk::Point2i{ 20, 13 }, mk::Point2i{ 40, 80 }, mk::Color::Red(), *target);
    rasterizer.drawLine(mk::Point2i{ 80, 40 }, mk::Point2i{ 13, 20 }, mk::Color::Red(), *target);

    context->drawIndexed(indexBuffer->size(), 0, 0);

    sf::RenderWindow window(sf::VideoMode(width, height), "Test");

    auto pixelData = reinterpret_cast<uint8_t*>(target->data());

    sf::Image image;
    image.create(width, height, pixelData);

    image.flipVertically();

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}