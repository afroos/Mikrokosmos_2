module;

#include <vector>

export module Mikrokosmos.Graphics.Rendering.Mesh;

import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class Mesh
	{
	public:

		Mesh() = default;

		std::size_t vertexCount() const
		{
			return _positions.size();
		}

	private:

		std::vector<Point3d>  _positions;
		std::vector<Color>    _colors;
		//std::vector<Vector3d> _normals;
		//std::vector<Vector2d> _textureCoordinates;
		//std::vector<Vector3f> _tangents;
		//std::vector<Vector3f> _bitangents;

		std::vector<std::size_t> _indices;

	};
}

/*
Scene
	SceneObject
		Light
		Camera
		Model
			

Model
	Meshes
	Effects


*/