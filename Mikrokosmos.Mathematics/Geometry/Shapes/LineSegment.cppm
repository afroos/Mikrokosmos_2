module;

#include <cstddef>

export module Mikrokosmos_Mathematics_Geometry_LineSegment;

import Mikrokosmos_Mathematics_Algebra_Vector; // why?
import Mikrokosmos_Mathematics_Geometry_Point;

export
{
	namespace mk 
	{
		template <std::size_t Dimension, typename CoordinateType>
		class LineSegment
		{

		public:
			LineSegment()
			{
			}
			LineSegment(const Point<Dimension, CoordinateType>& p0, const Point<Dimension, CoordinateType>& p1)
				: 
				_p0{ p0 }, 
				_p1{ p1 }
			{
			}

			Point<Dimension, CoordinateType> p0() const 
			{ 
				return _p0; 
			}

			Point<Dimension, CoordinateType> p1() const
			{
				return _p1;
			}

		private:

			Point<Dimension, CoordinateType> _p0;
			Point<Dimension, CoordinateType> _p1;
		};
	
		using LineSegment2  = LineSegment<2, double>;
		using LineSegment2i = LineSegment<2, int>;
		using LineSegment2f = LineSegment<2, float>;
		using LineSegment2d = LineSegment<2, double>;

		using LineSegment3  = LineSegment<3, double>;
		using LineSegment3i = LineSegment<3, int>;
		using LineSegment3f = LineSegment<3, float>;
		using LineSegment3d = LineSegment<3, double>;
	}
}