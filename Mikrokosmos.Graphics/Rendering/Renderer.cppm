module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.Renderer;

//import Mikrokosmos.Graphics.Color;
//import Mikrokosmos.Graphics.Rendering.Buffer;
//import Mikrokosmos.Graphics.Rendering.Mesh;
//import Mikrokosmos.Graphics.Rendering.Framebuffer;
//import Mikrokosmos.Graphics.Rendering.Shader;
import Mikrokosmos.Graphics.SceneGraph.Camera;
import Mikrokosmos.Graphics.SceneGraph.Light;
import Mikrokosmos.Graphics.SceneGraph.Model;
import Mikrokosmos.Graphics.SceneGraph.Node;
import Mikrokosmos.Graphics.SceneGraph.Scene;

export namespace mk
{
	class Renderer
	{
	public:

		Renderer() = default;

		void clearBuffers()
		{

		}

		void draw(const std::shared_ptr<Scene>& scene)
		{

		}

		//void draw(const Mesh& mesh, const Shader& shader, Framebuffer& framebuffer)
		//{
			/*
			Vertex processing
				Vertex shader
			Primitive processing
				Primitive assembly
				Viewport transformation
				Clipping
			Rasterization
				Rasterization
				Face culling
			Fragment processing
				Tests
				Fragment shader
			Pixel processing
				Blend
				Depth
				Stencil
			*/

			// Vertex specification
			// Vertex shader
			// Primitive assembly
			// Clipping
			// Viewport transformation
			// Backface culling
			// Rasterization
			// Fragment shader
			// Framebuffer processing
		//}

	//private:

	};
}