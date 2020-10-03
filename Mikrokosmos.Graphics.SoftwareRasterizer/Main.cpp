#include <SFML/Graphics.hpp>
#include <string>
#include <cstdint>

import Mikrokosmos_Mathematics_Geometry;
//import Mikrokosmos_Mathematics_Geometry_Point;
//import Mikrokosmos_Mathematics_Geometry_LineSegment;
import Mikrokosmos_Graphics;

int main()
{
    mk::Rasterizer rasterizer;

    auto pixelBuffer = mk::Buffer<mk::Color>(100, 100);

    rasterizer.drawLine(mk::Point2i{ 13, 20 }, mk::Point2i{ 80, 40 }, mk::Color::White(), pixelBuffer);
    rasterizer.drawLine(mk::Point2i{ 20, 13 }, mk::Point2i{ 40, 80 }, mk::Color::Red(), pixelBuffer);
    rasterizer.drawLine(mk::Point2i{ 80, 40 }, mk::Point2i{ 13, 20 }, mk::Color::Red(), pixelBuffer);

    sf::RenderWindow window(sf::VideoMode(100, 100), "Teste");

    auto pixelData = reinterpret_cast<uint8_t*>(pixelBuffer.data());

    sf::Image image;
    image.create(100, 100, pixelData);

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