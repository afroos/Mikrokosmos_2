#include <cstdint>
#include <cmath>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <span>
#include <string>

#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

import Mikrokosmos.Containers;
import Mikrokosmos.Debugging;
import Mikrokosmos.Graphics;
import Mikrokosmos.Mathematics.Algebra;
import Mikrokosmos.Mathematics.Geometry;
import Mikrokosmos.Platform.SFML.SFMLSwapChainPresenter;

int main()
{
  /*  std::vector<mk::Vertex> vertexes;
    std::vector<mk::Index> indexes;

    std::ifstream in;
    in.open("african_head.obj", std::ifstream::in);
    if (in.fail()) return 69;
    std::string line;
    while (!in.eof()) 
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) 
        {
            iss >> trash;
            mk::Vector3f position;  mk::Vertex vertex;
            float v;
            for (int i = 0; i < 3; i++) 
            { 
                iss >> v; 
                vertex.position()[i] = v * 0.99f; 
            }
            vertex.position().w() = 1.0f;
            vertex.color() = mk::Color::White();
            vertexes.push_back(vertex);
        } 
        else if (!line.compare(0, 2, "f ")) 
        {
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) 
            {
                idx--; // in wavefront obj all indices start at 1, not zero
                indexes.push_back(idx);
            }
        }

    }*/

    auto width = 800;
    auto height = 800;

    auto device = std::make_shared<mk::Device>();

    sf::RenderWindow window(sf::VideoMode(width, height), "Hello Triangle");

    auto presenter = std::make_shared<mk::SFMLSwapChainPresenter>(window);

    auto swapChain = device->createSwapChain(width, height, presenter.get());

    //target->fill(mk::Color{ 100, 149, 237 });
    
    auto renderTargetView = device->createRenderTargetView(&swapChain->backBuffer());

    auto context = device->immediateContext();

    mk::Vertex vertexes[] =
    {
        { {-0.5f, -0.5f, +0.0f}, mk::Color::Red()   },
        { {+0.5f, -0.5f, +0.0f}, mk::Color::Green() },
        { {+0.0f, +0.5f, +0.0f}, mk::Color::Blue()  },
        { {+0.5f, +0.0f, +0.0f}, mk::Color::Yellow()  }
    };

    auto vertexBuffer = device->createVertexBuffer(vertexes);

    mk::Index indexes[] = {0, 1, 2};

    auto indexBuffer = device->createIndexBuffer(indexes);

    context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::TriangleList);
    context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
    context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

    auto vertexShader = device->createVertexShader("Basic");

    context->vertexShaderStage()->setShader(vertexShader);

    //context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Wireframe });
    context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Solid });
    context->rasterizerStage()->setViewport({ 0.0, 0.0, (float)width, (float)height });

    auto fragmentShader = device->createFragmentShader("");

    context->fragmentShaderStage()->setShader(fragmentShader);

    context->outputMergerStage()->setRenderTargetView(*renderTargetView);


                //auto effect = std::make_shared<mk::Effect>();
   
                //auto triangle = std::make_shared<mk::Mesh>(vertexBuffer, indexBuffer, effect);

    const auto radius = 5.0f;

    auto angle = 0.0f;

    auto model = mk::Matrix44f::Identity();
    
    auto projection = mk::Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, radius * 2.0f);

    context->fragmentShaderStage()->shader()->_ambientColor = mk::Color{1.0f, 0.0f, 0.0f, 0.25f};
    context->fragmentShaderStage()->shader()->_ambientIntensity = 1.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        auto start = std::chrono::high_resolution_clock::now();

        renderTargetView->clear(mk::Color::Black());

        angle += 0.01f;
        float camX = std::sin(angle) * radius;
        float camZ = std::cos(angle) * radius;

        auto view = mk::LookAt(mk::Point3f{ camX, 0.0f, camZ }, mk::Point3f{ 0.0f, 0.0f, 0.0f }, mk::Vector3f{0.0, 1.0, 0.0});

        context->vertexShaderStage()->shader()->modelViewProjection() = /*projection * view * model*/ mk::Matrix44f::Identity();

        context->drawIndexed(indexBuffer->size(), 0, 0);

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Elapsed time: " << elapsed.count() << " s\n";
        
        swapChain->present();
    }

    return 0;
}