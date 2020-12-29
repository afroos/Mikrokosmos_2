module;

#include <array>
#include <cassert>
#include <cmath>

export module Mikrokosmos.Mathematics.Algebra.Vector;

export
{
	namespace mk 
	{
		using Index = std::size_t;

		template <std::size_t Dimension, typename Scalar>
		class Vector
		{
		public:

			constexpr Vector() = default;

			template<typename... CoordinateList> requires (sizeof...(CoordinateList) == Dimension)
			constexpr Vector(CoordinateList&&... coordinates) noexcept
				: _coordinates{ static_cast<Scalar>(coordinates)... }
			{
			}


			constexpr Vector(const Vector<3, Scalar>& vector, Scalar w) requires (Dimension == 4)
				: _coordinates{ vector[0], vector[1], vector[2], w }
			{
			}

			static constexpr Vector Zero() noexcept { return Vector(); }

			constexpr const Scalar& operator[](Index index) const
			{
				assert(index < _coordinates.size());
				return _coordinates[index];
			}

			constexpr Scalar& operator[](Index index)
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

			constexpr Scalar& w() requires (Dimension > 3) { return _coordinates[3]; }

			constexpr const Scalar& w() const requires (Dimension > 3) { return _coordinates[3]; }

			constexpr Vector& operator-=(const Vector& other) noexcept
			{
				for (Index i = 0; i < Dimension; ++i)
				{
					(*this)[i] -= other[i];
				}
				return *this;
			}

			constexpr Vector& operator*=(const Scalar scalar) noexcept
			{
				for (Index i = 0; i < Dimension; ++i)
				{
					(*this)[i] *= scalar;
				}
				return *this;
			}
			
			constexpr Vector& operator/=(const Scalar scalar) noexcept
			{
				auto inverseScalar = Scalar{ 1 } / scalar;

				*this *= inverseScalar;

				return *this;
			}

		private:
			std::array<Scalar, Dimension> _coordinates{ };
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

		template <std::size_t Dimension, typename Scalar>
		constexpr Vector<Dimension, Scalar> operator-(const Vector<Dimension, Scalar>& vector1, const Vector<Dimension, Scalar>& vector2) noexcept
		{
			Vector<Dimension, Scalar> result{ vector1 };
			result -= vector2;
			return result;
		}

		template <std::size_t Dimension, typename Scalar>
		constexpr Vector<Dimension, Scalar> operator*(Scalar scalar, const Vector<Dimension, Scalar>& vector) noexcept
		{
			Vector<Dimension, Scalar> result{ vector };
			result *= scalar;
			return result;
		}

		template <std::size_t Dimension, typename Scalar>
		constexpr Vector<Dimension, Scalar> operator/(const Vector<Dimension, Scalar>& vector, Scalar scalar) noexcept
		{
			Vector<Dimension, Scalar> result{ vector };
			result /= scalar;
			return result;
		}

		template <std::size_t Dimension, typename Scalar>
		constexpr Scalar dot(const Vector<Dimension, Scalar>& vector1, const Vector<Dimension, Scalar>& vector2) noexcept
		{
			auto result = Scalar{ 0 };
			for (Index i = 0; i < Dimension; ++i)
			{
				result += vector1[i] * vector2[i];
			}
			return result;
		}

		template <std::size_t Dimension, typename Scalar>
		constexpr Scalar lengthSquared(const Vector<Dimension, Scalar>& vector) noexcept
		{
			return dot(vector, vector);
		}

		template <std::size_t Dimension, typename Scalar>
		constexpr Scalar length(const Vector<Dimension, Scalar>& vector) noexcept
		{
			return (float) std::sqrt((double) lengthSquared(vector));
		}

		template <std::size_t Dimension, typename Scalar>
		constexpr Vector<Dimension, Scalar> normalize(const Vector<Dimension, Scalar>& vector) noexcept
		{
			Scalar length2 = length(vector);

			if (length2 != 0.0f) return (vector / length2);
			else return Vector<Dimension, Scalar>::Zero();
		}

		template <typename Scalar>
		constexpr Vector<3, Scalar> cross(const Vector<3, Scalar>& vector1, const Vector<3, Scalar>& vector2) noexcept
		{
			Vector<3, Scalar> result;
			
			result.x() = vector1.y() * vector2.z() - vector1.z() * vector2.y();
			result.y() = vector1.z() * vector2.x() - vector1.x() * vector2.z();
			result.z() = vector1.x() * vector2.y() - vector1.y() * vector2.x();

			return result;
		}

	}
}