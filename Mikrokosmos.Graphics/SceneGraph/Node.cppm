module;

#include <memory>
#include <string>
#include <vector>

export module Mikrokosmos.Graphics.SceneGraph.Node;

export namespace mk
{
	class Node
	{
	public:

		Node(const std::string& name)
			:
			name_{ name }
		{

		}

		virtual ~Node() = default;

	protected:

		std::string name_;
		// Transform transform_

		std::vector<std::shared_ptr<Node>> children_;
	};
}