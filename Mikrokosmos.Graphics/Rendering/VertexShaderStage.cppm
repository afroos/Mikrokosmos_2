module;

#include <memory>
#include <vector>
#include <iostream>

export module Mikrokosmos.Graphics.Rendering.VertexShaderStage;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexShader;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{
	class VertexShaderStage
	{
	public:

		VertexShaderStage()
			:
			_shader{std::make_shared<VertexShader>()}
		{

		}

		void setShader(std::shared_ptr<VertexShader> shader)
		{
			_shader = shader;
		}

		std::shared_ptr<VertexShader> shader() const { return _shader; }

		VertexStream process(const VertexStream& vertexStream)
		{
			processedVertexes.resize(vertexStream.vertexCount());
			
			auto outputVertexStream = vertexStream;

			std::size_t index = 0;
			for (auto vertex : vertexStream.vertexes())
			{
				processedVertexes[index] = _shader->process(vertex);
				index++;
			}

			outputVertexStream.updateVertexes(processedVertexes);
			
			return outputVertexStream;
		}

		

	private:
		std::vector<Vertex> processedVertexes;

		std::shared_ptr<VertexShader> _shader;

	};
}