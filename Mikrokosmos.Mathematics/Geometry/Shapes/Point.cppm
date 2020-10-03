module;

#include <cstddef>

export module Mikrokosmos_Mathematics_Geometry_Point;
import Mikrokosmos_Mathematics_Algebra_Vector;

export
{
	namespace mk 
	{
		template <std::size_t Dimension, typename CoordinateType>
		class Point
		{

		public:

			constexpr Point() = default;

			template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == Dimension>>
			constexpr Point(Args&&... args)
				: _coordinates{ args... }
			{
			}

			constexpr const CoordinateType& operator[](std::size_t index) const
			{
				//assert(index < coords.size());
				return _coordinates[index];
			}

			constexpr CoordinateType& operator[](std::size_t index)
			{
				//assert(index < coords.size());
				return _coordinates[index];
			}

			template<typename = std::enable_if_t<(Dimension > 0)>>
			constexpr CoordinateType x() const { return _coordinates[0]; }

			template<typename = std::enable_if_t<(Dimension > 1)>>
			constexpr CoordinateType y() const { return _coordinates[1]; }

			template<typename = std::enable_if_t<(Dimension > 2)>>
			constexpr CoordinateType z() const { return _coordinates[2]; }

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
}