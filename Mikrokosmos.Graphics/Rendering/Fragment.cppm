module;

//#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Fragment;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class Fragment
	{

	public:

		Fragment() = default;

	private:

		Point2i _position;
		float _depth;
		Color _color;
		Vector3f _normal;
		Vector2f _textureCoordinates;
		// primitive id?
	};
}