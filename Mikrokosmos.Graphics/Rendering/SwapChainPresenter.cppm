module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.SwapChainPresenter;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;

export namespace mk 
{

	class SwapChainPresenter
	{
	public:

		SwapChainPresenter() = default;

		virtual void initialize(std::size_t width, std::size_t height) {}
		
		virtual void present(Color* pixels) {}

	};
}