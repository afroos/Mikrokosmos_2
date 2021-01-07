module;

#include <array>
#include <cassert>
#include <ostream>
#include <span>

export module Mikrokosmos.Mathematics.Algebra.Matrix;

import Mikrokosmos.Mathematics.Algebra.Vector;

using Index = std::size_t;

export namespace mk 
{
	template <std::size_t NumRows, std::size_t NumColumns, typename Scalar>
	class Matrix
	{

	public:

		class Row 
		{
			friend class Matrix;

		public:
				
			constexpr Row() = delete;

			constexpr std::size_t size() const noexcept { return _matrix.columns(); }

			constexpr Scalar& operator[](Index column) noexcept
			{
				assert(column < _matrix.columns());
				return _matrix(_row, column);
			}

		private:

			constexpr Row(Matrix& matrix, Index row) noexcept
				:
				_matrix{ matrix },
				_row{ row }
			{
			}

			Matrix& _matrix;
			Index _row;
		};

		class ConstRow
		{
			friend class Matrix;

		public:

			constexpr ConstRow() = delete;

			constexpr const Scalar& operator[](Index column) const noexcept
			{
				assert(column < _matrix.columns());
				return _matrix(_row, column);
			}

		private:

			constexpr ConstRow(const Matrix& matrix, Index row) noexcept
				:
				_matrix{ matrix },
				_row{ row }
			{
			}

			const Matrix& _matrix;
			Index _row;
		};

		constexpr Matrix()
		{
			std::array < Scalar, NumColumns> row{};
			row.fill(Scalar{ 0 });
			_elements.fill(row);
		}

		constexpr Matrix(std::initializer_list<std::initializer_list<Scalar>> elements)
		{
			for (Index row = 0; row < rows(); ++row)
			{
				for (Index column = 0; column < columns(); ++column)
				{
					_elements[row][column] = *elements.begin()->begin() + row * NumColumns + column;
				}
			}
		}

		static constexpr Matrix Identity() noexcept
		{
			Matrix result;
			for (Index i = 0; i < result.rows(); ++i)
			{
				result(i, i) = Scalar{ 1 };
			}
			return result;
		}

		constexpr std::size_t rows() const noexcept { return NumRows; }

		constexpr std::size_t columns() const noexcept { return NumColumns; }

		constexpr Row operator[](Index row)
		{
			assert(row < rows());
			return Row{ *this, row };
		}

		constexpr ConstRow operator[](Index row) const
		{
			assert(row < rows());
			return ConstRow{ *this, row };
		}

		constexpr Scalar& operator()(Index row, Index column) noexcept
		{
			return _elements[row][column];
		}

		constexpr const Scalar& operator()(Index row, Index column) const noexcept
		{
			return _elements[row][column];
		}

	private:
		std::array<std::array<Scalar, NumColumns>, NumRows> _elements; // Row-major storage.
	};

	template <std::size_t NumRows1, std::size_t NumColumns1, std::size_t NumRows2, std::size_t NumColumns2, typename Scalar>
	constexpr Matrix<NumRows1, NumColumns2, Scalar> operator*(const Matrix<NumRows1, NumColumns1, Scalar>& matrix1, const Matrix<NumRows2, NumColumns2, Scalar>& matrix2)
		requires (NumColumns1 == NumRows2)
	{
		Matrix<NumRows1, NumColumns2, Scalar> result;
		for (Index row = 0; row < result.rows(); ++row)
		{
			for (Index column = 0; column < result.columns(); ++column)
			{
				result(row, column) = Scalar{ 0 };
				for (Index i = 0; i < matrix1.columns(); ++i)
				{
					result[row][column] += matrix1[row][i] * matrix2[i][column];
				}
			}
		}
		return result;
	}

	template <std::size_t NumRows, std::size_t NumColumns, typename Scalar>
	constexpr Vector<NumColumns, Scalar> operator*(Matrix<NumRows, NumColumns, Scalar>& matrix, const Vector<NumColumns, Scalar>& vector)
	{
		Vector<NumColumns, Scalar> result;
		for (Index row = 0; row < matrix.rows(); ++row)
		{
			result[row] = Scalar{ 0 };
			for (Index column = 0; column < matrix.columns(); ++column)
			{
				result[row] += matrix[row][column] * vector[column];
			}
		}
		return result;
	}

	using Matrix22  = Matrix<2, 2, double>;
	using Matrix22i = Matrix<2, 2, int>;
	using Matrix22f = Matrix<2, 2, float>;
	using Matrix22d = Matrix<2, 2, double>;

	using Matrix33  = Matrix<3, 3, double>;
	using Matrix33i = Matrix<3, 3, int>;
	using Matrix33f = Matrix<3, 3, float>;
	using Matrix33d = Matrix<3, 3, double>;

	using Matrix44  = Matrix<4, 4, double>;
	using Matrix44i = Matrix<4, 4, int>;
	using Matrix44f = Matrix<4, 4, float>;
	using Matrix44d = Matrix<4, 4, double>;

	template <std::size_t NumRows, std::size_t NumColumns, typename Scalar>
	std::ostream& operator<<(std::ostream& out, const Matrix<NumRows, NumColumns, Scalar>& matrix) noexcept
	{
		for (Index row = 0; row < matrix.rows(); ++row)
		{
			out << "[ ";

			for (Index column = 0; column < matrix.columns(); ++column)
			{
				out << std::showpos << std::scientific << matrix[row][column];
				if (column < matrix.columns() - 1) out << ", ";
			}

			out << " ]";

			if (row < matrix.rows() - 1) out << '\n';
		}

		return out;
	}

}