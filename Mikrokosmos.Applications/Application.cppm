module;

#include <string>

export module Mikrokosmos.Applications.Application;

export namespace mk
{
	class Application
	{
	public:

		Application() = default;

		/*struct Configuration
		{
			std::string name{ "" };
		};*/

		virtual ~Application() = default;

		virtual int run()
		{
			return 0;
		}

	protected:

		

		/*Application(const Configuration& configuration)
			: 
			_name{ configuration.name }
		{

		}*/

	/*	Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;*/

		//std::string _name{"a"};

	};
}