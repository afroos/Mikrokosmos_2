#include <SFML/Graphics.hpp>
#include <string>
#include <cstdint>

import Mikrokosmos_Mathematics_Geometry;
import Mikrokosmos_Graphics;

int main()
{
    mk::Rasterizer rasterizer;

    mk::Framebuffer framebuffer{ 100, 100 };

    rasterizer.drawLine(mk::Point2i{ 13, 20 }, mk::Point2i{ 80, 40 }, mk::Color::White(), framebuffer);
    rasterizer.drawLine(mk::Point2i{ 20, 13 }, mk::Point2i{ 40, 80 }, mk::Color::Red(), framebuffer);
    rasterizer.drawLine(mk::Point2i{ 80, 40 }, mk::Point2i{ 13, 20 }, mk::Color::Red(), framebuffer);

    sf::RenderWindow window(sf::VideoMode(100, 100), "Teste");

    auto colorBufferData = reinterpret_cast<uint8_t*>(framebuffer.colorBufferData());

    sf::Image image;
    image.create(100, 100, colorBufferData);

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