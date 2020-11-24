module;

#include <array>

export module Mikrokosmos.Mathematics.Algebra.Vector;

export
{
	namespace mk 
	{
		template <std::size_t Dimension, typename CoordinateType>
		class Vector
		{
		public:

			Vector() = default;

			template<typename... CoordinateList>
				requires (sizeof...(CoordinateList) == Dimension)
			Vector(CoordinateList&&... coordinates)
				: _coordinates{ coordinates... }
			{
			}

			const CoordinateType& operator[](std::size_t index) const
			{
				//assert(index < coords.size());
				return _coordinates[index];
			}

			CoordinateType& operator[](std::size_t index)
			{
				//assert(index < coords.size());
				return _coordinates[index];
			}

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
	}
}