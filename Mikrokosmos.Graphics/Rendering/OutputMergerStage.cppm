module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.OutputMerger;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
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

		void process(const FragmentStream& fragmentStream)
		{
			for (auto fragment : fragmentStream)
			{
				_renderTargetView.at(fragment.position().y(), fragment.position().x()) = fragment.color();
			}
		}

	private:

		RenderTargetView _renderTargetView;
	};
}