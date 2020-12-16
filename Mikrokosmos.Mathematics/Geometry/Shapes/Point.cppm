module;

#include <cassert>
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
			: _coordinates( static_cast<CoordinateType>(coordinates)... )
		{
		}

		constexpr const CoordinateType& operator[](std::size_t index) const
		{
			assert(index < _coordinates.size());
			return _coordinates[index];
		}

		constexpr CoordinateType& operator[](std::size_t index)
		{
			assert(index < _coordinates.size());
			return _coordinates[index];
		}

		constexpr CoordinateType& x() requires (Dimension > 0) { return _coordinates[0]; }

		constexpr const CoordinateType& x() const requires (Dimension > 0) { return _coordinates[0]; }

		constexpr CoordinateType& y() requires (Dimension > 1) { return _coordinates[1]; }

		constexpr const CoordinateType& y() const requires (Dimension > 1) { return _coordinates[1]; }

		constexpr CoordinateType& z() requires (Dimension > 2) { return _coordinates[2]; }

		constexpr const CoordinateType& z() const requires (Dimension > 2) { return _coordinates[2]; }

		constexpr Vector<Dimension, CoordinateType> coordinates() const { return _coordinates; }

	private:

		Vector<Dimension, CoordinateType> _coordinates{};
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
