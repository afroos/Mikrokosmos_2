module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.IndexBuffer;

import Mikrokosmos.Core.Array;

export namespace mk
{
	using Index = std::size_t;
	using IndexBuffer = Array<1, Index>;
}