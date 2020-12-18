module;

#include <array>
#include <concepts>
#include <numeric>
#include <span>
#include <type_traits>
#include <vector>

export module Mikrokosmos.Core.Array;

export namespace mk
{
	template<typename Type>
	concept SizeType = std::is_convertible_v<Type, std::size_t>;

	template <std::size_t NumDimensions, typename ElementType>
	class Array
	{

	public:

		Array() = default;

		Array(std::span<ElementType> span) requires (NumDimensions == 1)
			: 
			_elements{ span.begin(), span.end() },
			_extents{ span.size() }
		{

		}

		template<SizeType... ExtentList> requires (sizeof...(ExtentList) == NumDimensions)
		Array(ExtentList&&... extents)
		{
			resize(extents...);
		}

		template<SizeType... IndexList> requires (sizeof...(IndexList) == NumDimensions)
		ElementType& at(IndexList&&... indices)
		{
			return _elements[computeOffset(indices...)];
		}

		template<SizeType... IndexList> requires (sizeof...(IndexList) == NumDimensions)
		const ElementType& at(IndexList&&... indices) const
		{
			return _elements[computeOffset(indices...)];
		}

		ElementType* begin()
		{
			return _elements.data();
		}

		const ElementType* begin() const
		{
			return _elements.data();
		}

		ElementType* end()
		{
			return _elements.data() + _elements.size();
		}

		const ElementType* end() const
		{
			return _elements.data() + _elements.size();
		}

		ElementType* data()
		{
			return _elements.data();
		}

		std::size_t size() const
		{
			return _elements.size();
		}

		std::size_t size(std::size_t i) const
		{
			return _extents[i];
		}
		
		std::size_t height() const requires (NumDimensions == 2 || NumDimensions == 3)
		{
			return size(0);
		}

		std::size_t width() const requires (NumDimensions == 2 || NumDimensions == 3)
		{
			return size(1);
		}

		std::size_t depth() const requires (NumDimensions == 3)
		{
			return size(2);
		}

		std::size_t numDimensions() const
		{
			return _extents.size();
		}

		template<typename... ExtentList>
		requires (sizeof...(ExtentList) == NumDimensions)
		void resize(ExtentList&&... extents)
		{
			_elements.resize((... * extents));
			_extents = { static_cast<std::size_t>(extents)... };
		}

		void fill(const ElementType& value)
		{
			std::fill(_elements.begin(), _elements.end(), value);
		}

	private:

		template<typename... IndexList>
			requires (sizeof...(IndexList) == NumDimensions)
		std::size_t computeOffset(IndexList... indices)
		{
			std::array<std::size_t, NumDimensions> indexes{ static_cast<std::size_t>(indices)... };

			auto offset = indexes[0];
			for (std::size_t i = 1; i < NumDimensions; ++i)
			{
				offset = offset * _extents[i] + indexes[i];
			}

			return offset;
		}

		std::vector<ElementType> _elements;
		std::array<std::size_t, NumDimensions> _extents;

	};

}