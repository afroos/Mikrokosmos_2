module;

#include <memory>
#include <string>
#include <unordered_map>

export module Mikrokosmos.Graphics.SceneGraph.Scene;

import Mikrokosmos.Graphics.SceneGraph.Camera;
import Mikrokosmos.Graphics.SceneGraph.Light;
import Mikrokosmos.Graphics.SceneGraph.Model;
import Mikrokosmos.Graphics.SceneGraph.Node;

export namespace mk
{
	class Scene
	{
	public:

		Scene() = default;

	private:

		std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
		std::unordered_map<std::string, std::shared_ptr<Light>> lights_;
		std::unordered_map<std::string, std::shared_ptr<Camera>> cameras_;
		std::unordered_map<std::string, std::shared_ptr<Model>> models_;

		std::shared_ptr<Camera> _activeCamera;
	};
}