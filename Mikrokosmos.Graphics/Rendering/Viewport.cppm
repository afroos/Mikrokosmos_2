module;

#include <cassert>

export module Mikrokosmos.Graphics.Rendering.Viewport;

export namespace mk
{
	class Viewport
	{

	public:

		Viewport() = default;

		Viewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f)
			:
			_x{ x },
			_y{ y },
			_width{ width  },
			_height{ height  },
			_minDepth{ minDepth },
			_maxDepth{ maxDepth }
		{
			assert(width >= 0.0f);
			assert(height >= 0.0f);
			assert(minDepth >= 0.0f && minDepth <= 1.0f);
			assert(maxDepth >= 0.0f && maxDepth <= 1.0f);
		}

		float x() { return _x; }
		
		float y() { return _y; }
		
		float width() { return _width; }
		
		float height() { return _height; }

		float minDepth() { return _minDepth; }

		float maxDepth() { return _maxDepth; }

	private:

		float _x{ 0.0f };
		float _y{ 0.0f };
		float _width{ 0.0f };
		float _height{ 0.0f };
		float _minDepth{ 0.0f };
		float _maxDepth{ 1.0f };

	};
}