module;

#include <cstdint>
#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.SwapChain;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.SwapChainPresenter;
import Mikrokosmos.Graphics.Rendering.Texture;


export namespace mk 
{

	class SwapChain
	{
	public:

		SwapChain() = delete;

		SwapChain(std::size_t width, std::size_t height, SwapChainPresenter* presenter)
			:
			_backBuffer{ height, width },
			_presenter{ presenter }
		{
			if (presenter) _presenter->initialize(width, height);
		}

		Texture2D& backBuffer() { return _backBuffer; }

		void present()
		{
			_presenter->present(_backBuffer.data());
		}

	private:

		Texture2D _backBuffer;
		SwapChainPresenter* _presenter;

	};

}