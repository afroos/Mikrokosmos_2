module;

#include <algorithm>
#include <cstddef>
#include <memory>
#include <span>

#include <iostream>

export module Mikrokosmos.Graphics.Rendering.InputAssemblerStage;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.PrimitiveStream;
import Mikrokosmos.Graphics.Rendering.PrimitiveTopology;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{
	class InputAssemblerStage
	{
	public:

		InputAssemblerStage() = default;

		std::shared_ptr<VertexBuffer> vertexBuffer() const { return _vertexBuffer; }
		
		std::shared_ptr<IndexBuffer> indexBuffer() const { return _indexBuffer; }
		
		PrimitiveTopology primitiveTopology() const { return _primitiveTopology; }

		void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
		{
			_vertexBuffer = vertexBuffer;
		}

		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			_indexBuffer = indexBuffer;
		}

		void setPrimitiveTopology(PrimitiveTopology primitiveTopology) 
		{ 
			_primitiveTopology = primitiveTopology; 

			switch (_primitiveTopology)
			{
			case mk::PrimitiveTopology::PointList:
				_primitiveSize = 1;
				_primitiveAssemblyStep = 1;
				break;
			case mk::PrimitiveTopology::LineList:
				_primitiveSize = 2;
				_primitiveAssemblyStep = 2;
				break;
			case mk::PrimitiveTopology::LineStrip:
				_primitiveSize = 2;
				_primitiveAssemblyStep = 1;
				break;
			case mk::PrimitiveTopology::TriangleList:
				_primitiveSize = 3;
				_primitiveAssemblyStep = 3;
				break;
			case mk::PrimitiveTopology::TriangleStrip:
				_primitiveSize = 3;
				_primitiveAssemblyStep = 1;
				break;
			default:
				_primitiveSize = 0;
				_primitiveAssemblyStep = 0;
			}
		}

		VertexStream generateVertexStreamIndexed(std::size_t indexCount, std::size_t startIndexLocation, std::size_t baseVertexLocation)
		{		
			return VertexStream{ *_vertexBuffer, *_indexBuffer, indexCount, startIndexLocation, baseVertexLocation };
		}

		PrimitiveStream generatePrimitiveStream(const VertexStream& vertexStream)
		{
			auto primitiveCount = vertexStream.size() / _primitiveSize;
			auto currentVertex = vertexStream.begin();

			PrimitiveStream primitiveStream(primitiveCount);
			
			std::size_t offset = 0;
			for (auto& primitive : primitiveStream)
			{
				auto vertexList = vertexStream.slice(offset, _primitiveSize);
				primitive = Primitive{ vertexList };
				offset += _primitiveAssemblyStep;
			}

			return primitiveStream;
		}

	private:

		std::shared_ptr<VertexBuffer> _vertexBuffer;
		std::shared_ptr<IndexBuffer> _indexBuffer;
		PrimitiveTopology _primitiveTopology;
		std::size_t _primitiveSize;
		std::size_t _primitiveAssemblyStep;
	};
}