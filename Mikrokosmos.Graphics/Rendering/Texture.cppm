module;

export module Mikrokosmos.Graphics.Rendering.Texture;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;

export namespace mk 
{
	using Texture1D = Array<1, Color>;
	using Texture2D = Array<2, Color>;
	using Texture3D = Array<3, Color>;
}