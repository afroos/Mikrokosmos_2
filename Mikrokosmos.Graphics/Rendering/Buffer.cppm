module;

#include <vector>

export module Mikrokosmos_Graphics_Rendering_Buffer;

export
{
	namespace mk 
	{
		template <typename T>
		class Buffer
		{
		public:

			Buffer() = delete;

			Buffer(std::size_t rows, std::size_t columns)
				: 
				_data(rows * columns),
				_stride{ columns }
			{
			}

			void set(std::size_t column, std::size_t row, const T& data)
			{
				_data[(row * _stride) + column] = data;
			}

			T* data()
			{
				return _data.data();
			}

			std::size_t rows() const { return _data.size() / _stride; }
			std::size_t columns() const { return _stride; }

		private:
			std::vector<T> _data;
			std::size_t _stride;
		};

	}
}