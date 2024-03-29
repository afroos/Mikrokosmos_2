module;

#include <cstddef>
#include <cmath>

export module Mikrokosmos.Mathematics.Geometry.Transformations.MatrixTransform;

import Mikrokosmos.Mathematics.Algebra.Matrix;
import Mikrokosmos.Mathematics.Algebra.Vector;
import Mikrokosmos.Mathematics.Geometry.Point;

using Index = std::size_t;

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
		constexpr Matrix<4, 4, Scalar> Rotation(const Vector<3, Scalar>& axis, Scalar angle) noexcept
		{
			const auto c = std::cos(angle);
			const auto s = std::sin(angle);
			auto u = normalize(axis);
			auto alpha = (Scalar{ 1 } - c) * u;

			Matrix<4, 4, Scalar> result;

			result[0][0] = c + alpha[0] * u[0];
			result[1][0] = alpha[0] * u[1] + s * u[2];
			result[2][0] = alpha[0] * u[2] - s * u[1];

			result[0][1] = alpha[1] * u[0] - s * u[2];
			result[1][1] = c + alpha[1] * u[1];
			result[2][1] = alpha[1] * u[2] + s * u[0];

			result[0][2] = alpha[2] * u[0] + s * u[1];
			result[1][2] = alpha[2] * u[1] - s * u[0];
			result[2][2] = c + alpha[2] * u[2];

			result[3][3] = Scalar{ 1 };

			return result;
		}

		template <typename Scalar>
		constexpr Matrix<4, 4, Scalar> LookAt(const Point<3, Scalar>&  eyePosition,
											  const Point<3, Scalar>&  targetPosition,
											  const Vector<3, Scalar>& upDirection) noexcept
		{
			auto backward = normalize(eyePosition - targetPosition);
			auto right = normalize(cross(upDirection, backward));
			auto up = cross(backward, right);
			
			Matrix<4, 4, Scalar> result;

			result[0][0] = right.x();
			result[1][0] = right.y();
			result[2][0] = right.z();

			result[0][1] = up.x();
			result[1][1] = up.y();
			result[2][1] = up.z();

			result[0][2] = backward.x();
			result[1][2] = backward.y();
			result[2][2] = backward.z();

			result[0][3] = -dot(right, eyePosition.coordinates());
			result[1][3] = -dot(up, eyePosition.coordinates());
			result[2][3] = -dot(backward, eyePosition.coordinates());
			
			result[3][3] = Scalar{ 1 };

			return result;
		}

		template <typename Scalar>
		constexpr Matrix<4, 4, Scalar> Orthographic(Scalar viewWidth, 
													Scalar viewHeight,
													Scalar nearPlaneDistance, 
													Scalar farPlaneDistance) noexcept
		{
			Matrix<4, 4, Scalar> result;

			auto depthRange = Scalar{ 1 } / (nearPlaneDistance - farPlaneDistance);

			result[0][0] = Scalar{ 2 } / viewWidth;
			
			result[1][1] = Scalar{ 2 } / viewHeight;
			
			result[2][2] = depthRange;
			result[2][3] = nearPlaneDistance * depthRange;
			
			result[3][3] =   Scalar{ 1 };

			return result;
		}

		template <typename Scalar>
		constexpr Matrix<4, 4, Scalar> Perspective(Scalar verticalFOV,
												   Scalar aspectRatio,
												   Scalar nearPlaneDistance,
												   Scalar farPlaneDistance) noexcept
		{
			Matrix<4, 4, Scalar> result;

			double halfVerticalFOV = 0.5 * verticalFOV;
			double cosFOV = std::cos(halfVerticalFOV);
			double sinFOV = std::sin(halfVerticalFOV);

			Scalar height = cosFOV / sinFOV;
			auto width = height / aspectRatio;
			auto depthRange = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

			result[0][0] = width;
			
			result[1][1] = height;
			
			result[2][2] = depthRange;
			result[2][3] = nearPlaneDistance * depthRange;

			result[3][2] = - Scalar{ 1 };
			result[3][3] = Scalar{ 1 };

			return result;
		}
		

	}
}