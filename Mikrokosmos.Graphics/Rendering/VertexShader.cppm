module;

#include <cstddef>
#include <memory>
#include <span>
#include <ostream>

export module Mikrokosmos.Graphics.Rendering.VertexShader;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Debugging;
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
			auto output{ vertex };
			
			return output;
		}

		Matrix44f _modelViewProjection{ Matrix44f::Identity() };

		Matrix44f _model{ Matrix44f::Identity() };


	private:

	};

	class BasicVertexShader : public VertexShader
	{
	public:

		BasicVertexShader() = default;	

		Vertex process(const Vertex& vertex) override
		{
			auto output{ vertex };

			output.position() = _modelViewProjection * vertex.position();
			
			output.normal() = _model * Vector4f{ vertex.normal(), 0.0f };
			
			return output;
		}
	};
}