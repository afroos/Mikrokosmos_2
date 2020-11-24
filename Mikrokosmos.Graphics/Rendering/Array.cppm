module;

#include <array>
#include <numeric>
#include <vector>

export module Mikrokosmos.Core.Array;

export namespace mk
{

	template <std::size_t NumDimensions, typename ElementType>
	class Array
	{

	public:

		Array() = default;

		template<typename... ExtentList>
			requires ( sizeof...(ExtentList) == NumDimensions)
		Array(ExtentList&&... extents)
		{
			resize(extents...);
		}

		template<typename... IndexList>
			requires (sizeof...(IndexList) == NumDimensions)
		ElementType& at(IndexList&&... indices)
		{
			return elements_[computeOffset(indices...)];
		}

		template<typename... IndexList>
		requires (sizeof...(IndexList) == NumDimensions)
		const ElementType& at(IndexList&&... indices) const
		{
			return elements_[computeOffset(indices...)];
		}

		ElementType* begin()
		{
			return elements_.data();
		}

		const ElementType* begin() const
		{
			return elements_.data();
		}

		ElementType* end()
		{
			return elements_.data() + elements_.size();
		}

		const ElementType* end() const
		{
			return elements_.data() + elements_.size();
		}

		ElementType* data()
		{
			return elements_.data();
		}

		std::size_t size() const
		{
			return elements_.size();
		}

		std::size_t size(std::size_t i) const
		{
			return extents_[i];
		}
		
		std::size_t height() requires (NumDimensions == 2 || NumDimensions == 3)
		{
			return size(0);
		}

		std::size_t width() requires (NumDimensions == 2 || NumDimensions == 3)
		{
			return size(1);
		}

		std::size_t depth() requires (NumDimensions == 3)
		{
			return size(2);
		}

		std::size_t numDimensions() const
		{
			return extents_.size();
		}

		template<typename... ExtentList>
		requires (sizeof...(ExtentList) == NumDimensions)
		void resize(ExtentList&&... extents)
		{
			elements_.resize((... * extents));
			extents_ = { std::size_t(extents)... };
		}

		void fill(const ElementType& value)
		{
			std::fill(elements_.begin(), elements_.end(), value);
		}
	
	private:

		template<typename... IndexList>
			requires (sizeof...(IndexList) == NumDimensions)
		std::size_t computeOffset(IndexList... indices)
		{
			std::array<std::size_t, NumDimensions> indexes{ std::size_t(indices)... };

			auto offset = indexes[0];
			for (std::size_t i = 1; i < NumDimensions; ++i)
			{
				offset = offset * extents_[i] + indexes[i];
			}

			return offset;
		}

		std::vector<ElementType> elements_;
		std::array<std::size_t, NumDimensions> extents_;

	};
}