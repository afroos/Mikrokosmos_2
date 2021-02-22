module;

#include <string>
#include <string_view>

#include <SFML/Graphics.hpp>

export module Mikrokosmos.Applications.WindowApplication;

import Mikrokosmos.Applications.Application;

export namespace mk
{
	class WindowApplication : public Application
	{
	public:

		WindowApplication() = delete;
		
		WindowApplication(std::string_view name, std::size_t windowWidth, std::size_t windowHeight)
			:
			Application{ name },
			_window{ sf::VideoMode{windowWidth, windowHeight}, std::string{name} },
			_windowWidth{ windowWidth },
			_windowHeight{ windowHeight },
			_windowAspectRatio{ static_cast<float>(windowWidth) / windowHeight }
		{
		}

		std::size_t windowWidth() const { return _windowWidth; }

		std::size_t windowHeight() const { return _windowHeight; }

		float windowAspectRatio() const { return _windowAspectRatio; }

	protected:

		bool shouldRun() override
		{	
			return _window.isOpen();
		}

		void processInput() override
		{
			sf::Event event;
			while (_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					_window.close();
			}
		}

		sf::RenderWindow _window;

	private:

		std::size_t _windowWidth;
		std::size_t _windowHeight;
		float _windowAspectRatio;

	};
}