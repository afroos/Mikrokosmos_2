module;

#include <cstddef>

export module Mikrokosmos.Mathematics.Geometry.Transformations.MatrixTransform;

import Mikrokosmos.Mathematics.Algebra.Matrix;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

export
{
	namespace mk 
	{

		template <std::size_t Dimension, typename Scalar>
		constexpr Matrix<Dimension + 1, Dimension + 1, Scalar> Translation(const Vector<Dimension, Scalar>& translation) noexcept
		{
			auto result = Matrix<Dimension + 1, Dimension + 1, Scalar>::Identity();

			for (Index row = 0; row < result.rows() - 1; ++row)
			{
				result[row][Dimension] = translation[row];
			}

			return result;
		}

		template <typename Scalar>
		constexpr Matrix<4, 4, Scalar> LookAt(const Point<3, Scalar>&  eyePosition,
											  const Point<3, Scalar>&  targetPosition,
											  const Vector<3, Scalar>& upDirection) noexcept
		{
			auto forward = normalize(targetPosition - eyePosition);
			auto left = normalize(cross(upDirection, forward));
			auto up = cross(forward, left);
			
			auto eyeToWorld = Matrix<4, 4, Scalar>::Identity();

			eyeToWorld[0][0] = left.x();
			eyeToWorld[1][0] = left.y();
			eyeToWorld[2][0] = left.z();
			eyeToWorld[0][1] = up.x();
			eyeToWorld[1][1] = up.y();
			eyeToWorld[2][1] = up.z();
			eyeToWorld[0][2] = forward.x();
			eyeToWorld[1][2] = forward.y();
			eyeToWorld[2][2] = forward.z();
			eyeToWorld[3][0] = eyePosition.x();
			eyeToWorld[3][1] = eyePosition.y();
			eyeToWorld[3][2] = eyePosition.z();

			return eyeToWorld;
		}

	}
}