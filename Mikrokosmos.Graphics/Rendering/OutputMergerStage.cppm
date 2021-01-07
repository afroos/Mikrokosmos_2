module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.OutputMerger;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.Pixel;
import Mikrokosmos.Graphics.Rendering.PixelStream;
import Mikrokosmos.Graphics.Rendering.RenderTargetView;

export namespace mk
{
	class OutputMergerStage
	{
	public:

		OutputMergerStage() = default;

		void setRenderTargetView(const RenderTargetView& renderTargetView)
		{
			_renderTargetView = renderTargetView;
		}

		void process(const PixelStream& pixelStream)
		{
			for (auto pixel : pixelStream)
			{
				auto x = pixel.position().x();
				auto y = pixel.position().y();

				_renderTargetView.at(pixel.position().y(), pixel.position().x()) = pixel.color();
			}
		}

	private:

		RenderTargetView _renderTargetView;
	};
}