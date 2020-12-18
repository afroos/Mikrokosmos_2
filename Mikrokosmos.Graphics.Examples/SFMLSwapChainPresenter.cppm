module;

#include <cstddef>
#include <SFML/Graphics.hpp>

export module Mikrokosmos.Graphics.Rendering.SFMLSwapChainPresenter;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.SwapChainPresenter;

export namespace mk 
{

	class SFMLSwapChainPresenter : public SwapChainPresenter
	{
	public:

		SFMLSwapChainPresenter() = default;

		SFMLSwapChainPresenter(sf::RenderWindow& window)
			:
			_window{ window }
		{
		}

		void initialize(std::size_t width, std::size_t height) override
		{
			_width = width;
			_height = height;
		}
		
		void present(Color* pixels) override
		{
			_image.create(_width, _height, reinterpret_cast<uint8_t*>(pixels));
			//_image.flipVertically();
			_texture.loadFromImage(_image);
			sf::Sprite sprite(_texture);

			_window.clear();
			_window.draw(sprite);
			_window.display();
		}

	private:

		std::size_t _width; 
		std::size_t _height;

		sf::RenderWindow& _window;
		sf::Image _image;
		sf::Texture _texture;

	};
}