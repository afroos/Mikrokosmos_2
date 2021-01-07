module;

export module Mikrokosmos.Graphics.Rendering.Pixel;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class Pixel
	{

	public:

		Pixel() = default;

		Pixel(const Point2i& position, float depth, const Color& color)
			:
			_position{ position },
			_depth{ depth },
			_color{ color }
		{
		}

		Point2i& position() { return _position; }

		const Point2i& position() const { return _position; }

		float& depth() { return _depth; }

		const float& depth() const { return _depth; }

		Color& color() { return _color; }

		const Color& color() const { return _color; }

	private:

		Point2i _position;
		float _depth;
		Color _color;
	};

}