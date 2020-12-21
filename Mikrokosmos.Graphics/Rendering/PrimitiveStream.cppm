module;

#include <vector>

export module Mikrokosmos.Graphics.Rendering.PrimitiveStream;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexBuffer;
import Mikrokosmos.Graphics.Rendering.VertexStream;

export namespace mk
{
	using PrimitiveStream = std::vector<Primitive>;
}