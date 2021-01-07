module;

export module Mikrokosmos.Graphics.Rendering.FragmentShader;

import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.Pixel;

export namespace mk
{
	class FragmentShader
	{
	public:

		FragmentShader() = default;

		virtual Pixel process(const Fragment& fragment)
		{
			Pixel result{ fragment.position(), fragment.depth(), fragment.color() };

			return result;
		}

		Color _ambientColor;

		float _ambientIntensity;

	private:

	};

	class BasicFragmentShader : public FragmentShader
	{
	public:

		BasicFragmentShader() = default;

		Pixel process(const Fragment& fragment) override
		{
			Pixel result{ fragment.position(), fragment.depth(), fragment.color() };

			result.color() = _ambientColor * _ambientIntensity;

			return result;
		}

	};

}