module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.IndexBuffer;

import Mikrokosmos.Core.Array;

export namespace mk
{
	using IndexBuffer = Array<2, std::size_t>;
}