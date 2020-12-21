module;

#include <cassert>
#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Primitive;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{
	class Primitive
	{

	public:

		Primitive() = default;

		Primitive(const VertexStream& vertexes)
			:
			_vertexes{ vertexes }
		{
		}

		VertexStream::Iterator begin()
		{
			return _vertexes.begin();
		}

		VertexStream::ConstIterator begin() const
		{
			return _vertexes.begin();
		}

		VertexStream::Iterator end()
		{
			return _vertexes.end();
		}

		VertexStream::ConstIterator end() const
		{
			return _vertexes.end();
		}
		
		std::size_t vertexCount() const
		{
			return _vertexes.size();
		}

		Vertex& vertex(std::size_t index)
		{
			return _vertexes[index];
		}

		const Vertex& vertex(std::size_t index) const
		{
			return _vertexes[index];
		}

	private:

		VertexStream _vertexes;
	};
}