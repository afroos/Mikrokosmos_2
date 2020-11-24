#include <SFML/Graphics.hpp>
#include <string>
#include <cstdint>
#include <iostream>

import Mikrokosmos.Mathematics.Geometry;
import Mikrokosmos.Graphics;
import Mikrokosmos.Core.Array;

int main()
{
    mk::Rasterizer rasterizer;


    mk::ColorBuffer colorBuffer{ 100, 100 };

    rasterizer.drawLine(mk::Point2i{ 13, 20 }, mk::Point2i{ 80, 40 }, mk::Color::White(), colorBuffer);
    rasterizer.drawLine(mk::Point2i{ 20, 13 }, mk::Point2i{ 40, 80 }, mk::Color::Red(), colorBuffer);
    rasterizer.drawLine(mk::Point2i{ 80, 40 }, mk::Point2i{ 13, 20 }, mk::Color::Red(), colorBuffer);

    sf::RenderWindow window(sf::VideoMode(100, 100), "Teste");

    auto colorBufferData = reinterpret_cast<uint8_t*>(colorBuffer.data());

    sf::Image image;
    image.create(100, 100, colorBufferData);

    image.flipVertically();

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);

    mk::Array<3, double> buffer(3, 4, 2);
    
    int x = 0;
    for (std::size_t i = 0; i < buffer.height(); ++i)
    {
        for (std::size_t j = 0; j < buffer.width(); ++j)
        {
            for (std::size_t k = 0; k < buffer.depth(); ++k)
            {
                buffer.at(i, j, k) = x++;
                std::cout << "(" << i << ", " << j << ", " << k << ")" << " = " << buffer.at(i, j, k) << "\n";
            }
        }
    }  

    for (const auto& element : buffer)
    {
        std::cout << "[" << element << "]" << "\n";
    }

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