module;

#include <array>
#include <cassert>

export module Mikrokosmos.Mathematics.Algebra.Vector;

export
{
	namespace mk 
	{
		template <std::size_t Dimension, typename CoordinateType>
		class Vector
		{
		public:

			constexpr Vector() = default;

			template<typename... CoordinateList> requires (sizeof...(CoordinateList) == Dimension)
			constexpr Vector(CoordinateList&&... coordinates)
				: _coordinates{ static_cast<CoordinateType>(coordinates)... }
			{
			}


			constexpr Vector(const Vector<3, CoordinateType>& vector, CoordinateType w) requires (Dimension == 4)
				: _coordinates{ vector[0], vector[1], vector[2], w }
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

			constexpr CoordinateType& w() requires (Dimension > 3) { return _coordinates[3]; }

			constexpr const CoordinateType& w() const requires (Dimension > 3) { return _coordinates[3]; }

		private:
			std::array<CoordinateType, Dimension> _coordinates{ };
		};

		using Vector2  = Vector<2, double>;
		using Vector2i = Vector<2, int>;
		using Vector2f = Vector<2, float>;
		using Vector2d = Vector<2, double>;

		using Vector3  = Vector<3, double>;
		using Vector3i = Vector<3, int>;
		using Vector3f = Vector<3, float>;
		using Vector3d = Vector<3, double>;

		using Vector4  = Vector<4, double>;
		using Vector4i = Vector<4, int>;
		using Vector4f = Vector<4, float>;
		using Vector4d = Vector<4, double>;
	}
}