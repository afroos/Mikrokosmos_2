module;

#include <string>
#include <string_view>

export module Mikrokosmos.Applications.Application;

export namespace mk
{
	class Application
	{
	public:

		Application() = default;

		Application(std::string_view name)
			:
			_name{ name }
		{
		}

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		virtual ~Application() = default;

		void run()
		{
			initialize();
			mainLoop();
			cleanup();
		}

		void mainLoop()
		{
			while (shouldRun())
			{
				processInput();
				update();
				render();
			}
		}

	protected:

		virtual void initialize()   {}
		virtual bool shouldRun()    { return false; }
		virtual void processInput() {}
		virtual void update()       {}
		virtual void render()       {}
		virtual void cleanup()      {}

	private:

		std::string _name{"Mikrokosmos Application"};

	};
}