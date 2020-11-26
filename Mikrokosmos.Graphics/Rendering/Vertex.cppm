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
			position_{ position },
			color_{ color }
		{
		}

		Point3f position() { return position_; }

	private:

		Point3f position_;
		Color color_;
		//Vector3f _normal;
		//Vector2f _textureCoordinates;

	};
}