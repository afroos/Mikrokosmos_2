module;

export module Mikrokosmos.Graphics.Rendering.Vertex;

import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class Vertex
	{

	public:

		Vertex() = default;

		Vertex(const Point3f& position, const Color& color)
			:
			_position{ position },
			_color{ color }
		{
		}

		Point3f position() { return _position; }

	private:

		Point3f _position;
		Color _color;
		//Vector3f _normal;
		//Vector2f _textureCoordinates;

	};
}