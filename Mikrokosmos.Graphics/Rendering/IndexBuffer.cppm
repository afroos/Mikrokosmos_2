module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.IndexBuffer;

import Mikrokosmos.Containers.Array;

export namespace mk
{
	using Index = std::size_t;
	using IndexBuffer = Array<1, Index>;
}