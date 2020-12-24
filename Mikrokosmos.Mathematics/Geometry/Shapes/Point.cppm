module;

#include <cassert>
#include <cstddef>

export module Mikrokosmos.Mathematics.Geometry.Point;

import Mikrokosmos.Mathematics.Algebra.Vector;

export namespace mk 
{
	template <std::size_t Dimension, typename Scalar>
	class Point
	{

	public:

		constexpr Point() = default;

		template<typename... CoordinateList> requires (sizeof...(CoordinateList) == Dimension)
		constexpr Point(CoordinateList&&... coordinates)
			: _coordinates( static_cast<Scalar>(coordinates)... )
		{
		}

		constexpr const Scalar& operator[](std::size_t index) const
		{
			assert(index < _coordinates.size());
			return _coordinates[index];
		}

		constexpr Scalar& operator[](std::size_t index)
		{
			assert(index < _coordinates.size());
			return _coordinates[index];
		}

		constexpr Scalar& x() requires (Dimension > 0) { return _coordinates[0]; }

		constexpr const Scalar& x() const requires (Dimension > 0) { return _coordinates[0]; }

		constexpr Scalar& y() requires (Dimension > 1) { return _coordinates[1]; }

		constexpr const Scalar& y() const requires (Dimension > 1) { return _coordinates[1]; }

		constexpr Scalar& z() requires (Dimension > 2) { return _coordinates[2]; }

		constexpr const Scalar& z() const requires (Dimension > 2) { return _coordinates[2]; }

		constexpr Vector<Dimension, Scalar> coordinates() const { return _coordinates; }

	private:

		Vector<Dimension, Scalar> _coordinates{};
	};
	
	using Point2  = Point<2, double>;
	using Point2i = Point<2, int>;
	using Point2f = Point<2, float>;
	using Point2d = Point<2, double>;

	using Point3  = Point<3, double>;
	using Point3i = Point<3, int>;
	using Point3f = Point<3, float>;
	using Point3d = Point<3, double>;

	template <std::size_t Dimension, typename Scalar>
	constexpr Vector<Dimension, Scalar> operator-(const Point<Dimension, Scalar>& point1, const Point<Dimension, Scalar>& point2) noexcept
	{
		return (point1.coordinates() - point2.coordinates());
	}

}
