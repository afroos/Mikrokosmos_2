module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.IndexBuffer;

import Mikrokosmos.Core.Array;

export namespace mk
{
	using IndexBuffer = Array<1, std::size_t>;
}