module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.Mesh;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Effect;
import Mikrokosmos.Graphics.Rendering.IndexBuffer;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;

export namespace mk
{
	class Mesh
	{
	public:

		Mesh() = default;

		Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer,
			 const std::shared_ptr<IndexBuffer>& indexBuffer,
			 const std::shared_ptr<Effect>& effect)
			:
			vertexBuffer_{ vertexBuffer },
			indexBuffer_ { indexBuffer },
			effect_ { effect }
		{

		}

	private:

		std::shared_ptr<VertexBuffer> vertexBuffer_;
		std::shared_ptr<IndexBuffer> indexBuffer_;
		std::shared_ptr<Effect> effect_;

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