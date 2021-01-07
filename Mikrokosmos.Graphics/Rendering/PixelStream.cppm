module;

#include <vector>

export module Mikrokosmos.Graphics.Rendering.PixelStream;

//import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Pixel;

export namespace mk
{
	using PixelStream = std::vector<Pixel>;
}