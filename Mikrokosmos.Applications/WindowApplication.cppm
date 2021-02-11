module;

#include <SFML/Graphics.hpp>

export module Mikrokosmos.Applications.WindowApplication;

import Mikrokosmos.Applications.Application;
import Mikrokosmos.Mathematics.Algebra.Vector;

export namespace mk
{
	class WindowApplication : public Application
	{
	public:

		struct Configuration
		{
			std::string name{ "Mikrokosmos Application" };
			Vector2u windowSize{ 800, 600 };
		};

		WindowApplication()
			:
			WindowApplication{ {.name = "Window Application", .windowSize = {800,600}} }
		{

		}


		WindowApplication(const Configuration& configuration)
			:
			_width{ configuration.windowSize.x() },
			_height{ configuration.windowSize.y() },
			_window{ sf::VideoMode{_width, _height}, configuration.name }
		{

		}

		std::size_t width() const { return _width; }

		std::size_t height() const { return _height; }

		virtual void initialize() noexcept
		{

		}

		int run() override
		{	
			initialize();

			while (_window.isOpen())
			{
				processInput();
				draw();
			}

			return 0;
		}

		virtual void processInput() noexcept
		{
			sf::Event event;
			while (_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					_window.close();
			}
		}

		virtual void draw() noexcept
		{

		}

	protected:

		std::size_t _width;
		std::size_t _height;
		sf::RenderWindow _window;

	private:

	};
}