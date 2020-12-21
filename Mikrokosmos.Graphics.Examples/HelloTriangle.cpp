#include <cstdint>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <span>
#include <string>


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics;
import Mikrokosmos.Mathematics.Algebra;
import Mikrokosmos.Platform.SFML.SFMLSwapChainPresenter;

int main()
{

    std::vector<mk::Vertex> vertexes;
    std::vector<mk::Index> indexes;

    std::ifstream in;
    in.open("african_head.obj", std::ifstream::in);
    if (in.fail()) return 69;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            mk::Vector3f position;  mk::Vertex vertex;
            float v;
            for (int i = 0; i < 3; i++) { iss >> v; vertex.position()[i] = v * 0.95f; }
            vertex.position().w() = 1.0f;
            vertex.color() = mk::Color::White();
            vertexes.push_back(vertex);
        } else if (!line.compare(0, 2, "f ")) {
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                indexes.push_back(idx);
            }
        }

    }

    auto width = 800;
    auto height = 800;

    auto device = std::make_shared<mk::Device>();

    sf::RenderWindow window(sf::VideoMode(width, height), "Hello Triangle");

    auto presenter = std::make_shared<mk::SFMLSwapChainPresenter>(window);

    auto swapChain = device->createSwapChain(width, height, presenter.get());

    //target->fill(mk::Color{ 100, 149, 237 });
    
    auto renderTargetView = device->createRenderTargetView(&swapChain->backBuffer());

    auto context = device->immediateContext();

   /* mk::Vertex vertexes[] =
    {
        { {-0.5f, -0.5f, +0.0f}, mk::Color::Red()   },
        { {+0.5f, -0.5f, +0.0f}, mk::Color::Green() },
        { {+0.0f, +0.5f, +0.0f}, mk::Color::Blue()  },
        { {+0.5f, +0.0f, +0.0f}, mk::Color::Yellow()  }
    };*/

    auto vertexBuffer = device->createVertexBuffer(vertexes);

   // mk::Index indexes[] = {0, 1, 2, 1, 3, 2, 1, 3, 0};

    auto indexBuffer = device->createIndexBuffer(indexes);

    context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::TriangleList);
    context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
    context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

    //context->vertexShaderStage()->setShader(vertexShader);

    context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Wireframe });
    context->rasterizerStage()->setViewport({ 0.0, 0.0, (float)width, (float)height });

    //context->pixelShaderStage()->setShader(pixelShader);

    context->outputMergerStage()->setRenderTargetView(*renderTargetView);

    context->drawIndexed(indexBuffer->size(), 0, 0);
    
    
    
                //auto vertexShader = device->createVertexShader(...);

                //auto effect = std::make_shared<mk::Effect>();
   
                //auto triangle = std::make_shared<mk::Mesh>(vertexBuffer, indexBuffer, effect);

    

    
    
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