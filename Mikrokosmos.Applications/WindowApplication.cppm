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
			std::string name{ "Test" };
			Vector2i windowSize{ 800, 600 };
		};

		WindowApplication()
			:
			WindowApplication{ {.name = "Window Application", .windowSize = {800,600}} }
		{

		}

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

		WindowApplication(const Configuration& configuration)
			:
			_window{ sf::VideoMode(configuration.windowSize.x(), configuration.windowSize.y()), configuration.name }
		{

		}

	private:

		sf::RenderWindow _window;

	};
}