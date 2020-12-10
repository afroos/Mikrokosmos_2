module;

#include <cstddef>
#include <iterator>
#include <memory>
#include <span>

export module Mikrokosmos.Graphics.Rendering.VertexStream;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;

export namespace mk
{
	class VertexStream
	{

	public:

		class Iterator
		{
		public:
			
			Iterator() = default;

			Iterator(Vertex* firstVertex, std::size_t* currentIndex, std::size_t baseVertexLocation)
				:
				_firstVertex{ firstVertex },
				_currentIndex{ currentIndex },
				_baseVertexLocation{ baseVertexLocation }
			{
			}

			Iterator operator++() 
			{ 
				++_currentIndex; 
				return *this; 
			}
			
			bool operator!=(const Iterator& other) const 
			{ 
				return (_firstVertex != other._firstVertex || _currentIndex != other._currentIndex); 
			}
			
			const Vertex& operator*() const 
			{ 
				return *(_firstVertex + *_currentIndex + _baseVertexLocation); 
			}

			Iterator operator+(std::size_t offset) 
			{ 
				return Iterator{_firstVertex, _currentIndex + offset, _baseVertexLocation }; 
			}

			std::size_t operator-(const Iterator& other) const
			{
				return (_currentIndex - other._currentIndex);
			}

		private:

			Vertex* _firstVertex;
			Index* _currentIndex;
			std::size_t _baseVertexLocation;

		};

		VertexStream() = default;

		VertexStream(VertexBuffer& vertexBuffer, 
			         IndexBuffer& indexBuffer, 
				     std::size_t indexCount, 
			         std::size_t startIndexLocation, 
			         std::size_t baseVertexLocation)
			:
			_vertexes{ vertexBuffer.data(), vertexBuffer.size() },
			_indexes{ indexBuffer.data() + startIndexLocation, indexCount },
			_baseVertexLocation{baseVertexLocation}
		{
		}

		std::size_t size() const
		{
			return _indexes.size();
		}

		bool empty() const
		{
			return _indexes.empty();
		}

		Iterator begin()
		{
			return Iterator{ _vertexes.data(), _indexes.data(), _baseVertexLocation };
		}

		const Iterator begin() const
		{
			return Iterator{ _vertexes.data(), _indexes.data(), _baseVertexLocation };
		}

		Iterator end()
		{
			return Iterator{ _vertexes.data(), _indexes.data() + _indexes.size(), _baseVertexLocation };
		}

		const Iterator end() const
		{
			return Iterator{ _vertexes.data(), _indexes.data() + _indexes.size(), _baseVertexLocation };
		}

		VertexStream slice(std::size_t offset, std::size_t size) const
		{
			VertexStream slice{ *this };
			slice._indexes = _indexes.subspan(offset, size);
			auto f = _indexes.front();
			auto l = _indexes.back();
			return slice;
		}

	private:

		std::span<Vertex> _vertexes;
		std::span<Index> _indexes;
		std::size_t _baseVertexLocation;
	};
}