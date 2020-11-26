module;

#include <cstddef>

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

		VertexStream() = default;

		VertexStream(std::size_t indexCount, std::size_t* startIndex, Vertex* startVertex)
			:
			startVertex_{ startVertex },
			startIndex_{ startIndex },
			indexCount_{ indexCount }
		{

		}

		class Iterator 
		{
		
		public:
			
			Iterator(Vertex* vertex, std::size_t* index) 
				: 
				vertex_{ vertex },
				index_{ index }
			{
			}
			
			Iterator operator++() 
			{ 
				++index_; 
				return *this; 
			}
			
			bool operator!=(const Iterator& other) const 
			{ 
				return ( vertex_ != other.vertex_ || index_ != other.index_ );			
			}
			
			const Vertex& operator*() const 
			{ 
				return *(vertex_ + *index_);
			}
		
		private:
			
			Vertex* vertex_;
			std::size_t* index_;

		};

		Iterator begin()
		{
			return Iterator(startVertex_, startIndex_);
		}

		const Iterator begin() const
		{
			return Iterator(startVertex_, startIndex_);
		}

		Iterator end()
		{
			return Iterator(startVertex_, startIndex_ + indexCount_);
		}

		const Iterator end() const
		{
			return Iterator(startVertex_, startIndex_ + indexCount_);
		}

	private:

		Vertex* startVertex_;
		std::size_t* startIndex_;
		std::size_t indexCount_;
	};
}