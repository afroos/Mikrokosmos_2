module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Primitive;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{
	class Primitive
	{

	public:

		Primitive() = default;

		Primitive(const VertexStream::Iterator& firstVertex, const VertexStream::Iterator& lastVertex)
			:
			_firstVertex{ firstVertex },
			_lastVertex{ lastVertex }
		{
		}

		std::size_t vertexCount() const
		{
			return (_lastVertex - _firstVertex);
		}

		Vertex vertex(std::size_t index)
		{
			// Assert
			return *(_firstVertex + index);
		}

	private:

		VertexStream::Iterator _firstVertex;
		VertexStream::Iterator _lastVertex;
	};
}