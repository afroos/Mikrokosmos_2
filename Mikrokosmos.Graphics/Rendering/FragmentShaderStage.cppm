module;

#include <memory>

export module Mikrokosmos.Graphics.Rendering.FragmentShaderStage;

import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentShader;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.Pixel;
import Mikrokosmos.Graphics.Rendering.PixelStream;

export namespace mk
{
	class FragmentShaderStage
	{
	public:

		FragmentShaderStage() = default;

		void setShader(std::shared_ptr<FragmentShader> shader)
		{
			_shader = shader;
		}

		std::shared_ptr<FragmentShader> shader() const { return _shader; }

		PixelStream process(const FragmentStream& fragmentStream)
		{
			_processedPixelStream.resize(fragmentStream.size());

			std::size_t index = 0;
			for (auto fragment : fragmentStream)
			{
				_processedPixelStream[index] = _shader->process(fragment);
				index++;
			}

			return _processedPixelStream;
		}



	private:
		PixelStream _processedPixelStream;

		std::shared_ptr<FragmentShader> _shader;

	};
}