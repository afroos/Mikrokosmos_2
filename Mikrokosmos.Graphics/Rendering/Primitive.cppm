module;

#include <cassert>
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

		const VertexStream::Iterator begin() const
		{
			return _firstVertex;
		}

		const VertexStream::Iterator end() const
		{
			return _lastVertex;
		}
		
		std::size_t vertexCount() const
		{
			return (_lastVertex - _firstVertex);
		}

		Vertex& vertex(std::size_t index)
		{
			assert(index < vertexCount());
			return *(_firstVertex + index);
		}

		//const Vertex& vertex(std::size_t index) const
		//{
		//	assert(index < vertexCount());
		//	return *(_firstVertex + index);
		//}

	private:

		VertexStream::Iterator _firstVertex{ nullptr, nullptr, 0U };
		VertexStream::Iterator _lastVertex{ nullptr, nullptr, 0U };
	};
}