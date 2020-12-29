module;

#include <cstddef>
#include <memory>
#include <span>

export module Mikrokosmos.Graphics.Rendering.VertexShader;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Mathematics.Algebra.Matrix;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Transformations.MatrixTransform;

export namespace mk
{
	class VertexShader
	{
	public:

		VertexShader() = default;

		virtual Vertex process(const Vertex& vertex)
		{
			auto result{ vertex };
			
			return result;
		}

		Matrix44f& modelViewProjection() { return _modelViewProjection; }

	protected:

		Matrix44f _modelViewProjection{ Matrix44f::Identity() };

	};

	class BasicVertexShader : public VertexShader
	{
	public:

		BasicVertexShader() = default;	

		Vertex process(const Vertex& vertex) override
		{
			auto result{ vertex };

			result.position() = _modelViewProjection * vertex.position();

			return result;
		}


	};
}