module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.RenderTargetView;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Texture;

export namespace mk 
{

	class RenderTargetView
	{
	public:

		RenderTargetView() = default;

		RenderTargetView(Texture2D* resource)
			:
			_resource{ resource }
		{
		}

		template<SizeType... IndexList>
		Color& at(IndexList&&... indices)
		{
			return _resource->at(indices...);
		}

		template<SizeType... IndexList>
		const Color& at(IndexList&&... indices) const
		{
			return _resource->at(indices...);
		}

		void clear(const Color& color)
		{
			_resource->fill(color);
		}

	private:

		Texture2D* _resource;

	};
}