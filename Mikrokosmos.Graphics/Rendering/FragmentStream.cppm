module;

#include <vector>

export module Mikrokosmos.Graphics.Rendering.FragmentStream;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	using FragmentStream = std::vector<Fragment>;
}