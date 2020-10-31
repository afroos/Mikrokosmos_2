module;

#include <vector>

export module Mikrokosmos_Graphics_Rendering_Buffer;

export namespace mk 
{
	template <typename T>
	class Buffer
	{
	public:

		Buffer() = default;

		Buffer(std::size_t width, std::size_t height)
		{
			resize(width, height);
		}

		T* data()
		{
			return _data.data();
		}

		std::size_t height() const { return _height; }
		std::size_t width() const { return _width; }

		void resize(std::size_t width, std::size_t height)
		{
			_data.resize(width * height);
			_width = width;
			_height = height;
		}

		T& at(std::size_t x, std::size_t y)
		{
			return _data[(y * _width) + x];
		}

		void set(std::size_t x, std::size_t y, const T& value)
		{
			_data[(y * _width) + x] = value;
		}

		void fill(const T& value)
		{
			std::fill(_data.begin(), _data.end(), value);
		}

	private:
		std::vector<T> _data;
		std::size_t _width{ 0 };
		std::size_t _height{ 0 };
	};
}