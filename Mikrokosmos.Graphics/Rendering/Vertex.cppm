module;

export module Mikrokosmos.Graphics.Rendering.Vertex;

import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class Vertex
	{

	public:

		Vertex() = default;

		Vertex(const Point3f& position, const Color& color)
			:
			_position{ position.coordinates(), 1.0f },
			_color{ color }
		{
		}

		Vector4f& position() { return _position; }

		const Vector4f& position() const { return _position; }

		Color& color() { return _color; }

		const Color& color() const { return _color; }

	private:

		Vector4f _position;
		Color _color;
		//Vector3f _normal;
		//Vector2f _textureCoordinates;

	};
}