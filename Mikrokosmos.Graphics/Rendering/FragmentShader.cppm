module;

#include <algorithm>

export module Mikrokosmos.Graphics.Rendering.FragmentShader;

import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.Pixel;
import Mikrokosmos.Mathematics.Algebra.Vector;

export namespace mk
{
	template<typename T>
	constexpr const T& saturate(const T& value)
	{
		return std::clamp(value, T{ 0 }, T{ 1 });
	}

	class FragmentShader
	{
	public:

		FragmentShader() = default;

		virtual Pixel process(const Fragment& fragment)
		{
			Pixel output{ fragment.position(), fragment.depth(), fragment.color() };

			return output;
		}

		Color _ambientColor;

		float _ambientIntensity;

		Vector3f _lightDirection;

	private:

	};

	class BasicFragmentShader : public FragmentShader
	{
	public:

		BasicFragmentShader() = default;

		Pixel process(const Fragment& fragment) override
		{
			Pixel output{ fragment.position(), fragment.depth(), fragment.color() };

			auto lightIntensity = saturate(dot(normalize(fragment.normal()), _lightDirection));

			output.color() = (_ambientColor * _ambientIntensity) * lightIntensity;

			return output;
		}

	};

}