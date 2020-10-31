module;

#include <cstddef>
#include <limits>
#include <vector>

export module Mikrokosmos_Graphics_Rendering_Framebuffer;

export import Mikrokosmos_Graphics_Color;
import Mikrokosmos_Graphics_Rendering_Buffer;

export namespace mk 
{
	class Framebuffer
	{
	public:

		Framebuffer() = default;

		Framebuffer(std::size_t width, std::size_t height)
		{
			resize(width, height);
		}

		std::size_t height() const { return _height; }
		std::size_t width() const { return _width; }

		double aspectRatio() const
		{
			return static_cast<double>(_width) / static_cast<double>(_height);
		}
		
		void resize(std::size_t width, std::size_t height)
		{
			_colorBuffer.resize(width, height);
			_depthBuffer.resize(width, height);
			_width = width;
			_height = height;
		}

		void clear()
		{
			_colorBuffer.fill(Color::Black());
			_depthBuffer.fill(std::numeric_limits<double>::infinity());
		}

		void setPixel(int x, int y, const Color& color)
		{
			_colorBuffer.at(x, y) = color;
		}

		void setPixel(int x, int y, double depth, const Color& color)
		{
			if (_depthBuffer.at(x, y) > depth)
			{
				_depthBuffer.at(x, y) = depth;
				_colorBuffer.at(x, y) = color;
			}
		}

		Color* colorBufferData()
		{
			return _colorBuffer.data();
		}


	private:
		Buffer<Color> _colorBuffer;
		Buffer<double> _depthBuffer;
		std::size_t _width{ 0 };
		std::size_t _height{ 0 };
	};
}