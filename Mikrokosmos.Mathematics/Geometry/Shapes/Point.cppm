module;

#include <cstddef>

export module Mikrokosmos.Mathematics.Geometry.Point;

import Mikrokosmos.Mathematics.Algebra.Vector;

export namespace mk 
{
	template <std::size_t Dimension, typename CoordinateType>
	class Point
	{

	public:

		constexpr Point() = default;

		template<typename... CoordinateList> requires (sizeof...(CoordinateList) == Dimension)
		constexpr Point(CoordinateList&&... coordinates)
			: coordinates_( static_cast<CoordinateType>(coordinates)... )
		{
		}

		constexpr const CoordinateType& operator[](std::size_t index) const
		{
			//assert(index < coords.size());
			return coordinates_[index];
		}

		constexpr CoordinateType& operator[](std::size_t index)
		{
			//assert(index < coords.size());
			return coordinates_[index];
		}

		constexpr CoordinateType x() const requires (Dimension > 0) { return coordinates_[0]; }

		constexpr CoordinateType y() const requires (Dimension > 1) { return coordinates_[1]; }

		constexpr CoordinateType z() const requires (Dimension > 2) { return coordinates_[2]; }

	private:

		Vector<Dimension, CoordinateType> coordinates_{};
	};
	
	using Point2  = Point<2, double>;
	using Point2i = Point<2, int>;
	using Point2f = Point<2, float>;
	using Point2d = Point<2, double>;

	using Point3  = Point<3, double>;
	using Point3i = Point<3, int>;
	using Point3f = Point<3, float>;
	using Point3d = Point<3, double>;
}
