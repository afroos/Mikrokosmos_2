module;

//#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Fragment;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class Fragment
	{

	public:

		Fragment() = default;

		Fragment(const Point2i& position, float depth, const Color& color, const Vector3f& normal, Vector2f textureCoordinates)
			:
			_position{ position },
			_depth{ depth },
			_color{ color },
			_normal{ normal },
			_textureCoordinates{ textureCoordinates }
		{
		}

		Point2i& position() { return _position; }

		const Point2i& position() const { return _position; }

		float& depth() { return _depth; }

		const float& depth() const { return _depth; }

		Color& color() { return _color; }

		const Color& color() const { return _color; }

		Vector3f& normal() { return _normal; }

		const Vector3f& normal() const { return _normal; }

	private:

		Point2i _position;
		float _depth;
		Color _color;
		Vector3f _normal;
		Vector2f _textureCoordinates;
		// primitive id?
	};

}