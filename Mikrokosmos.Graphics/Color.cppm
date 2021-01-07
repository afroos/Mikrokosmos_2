module;

#include <algorithm>
#include <cstdint>
#include <cstddef>

export module Mikrokosmos.Graphics.Color;

export namespace mk 
{
	class Color
	{
		
	public:

		constexpr Color() = default;

		constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) noexcept
			:
			_r{ red },
			_g{ green },
			_b{ blue },
			_a{ alpha }
		{
		}

		constexpr Color(int red, int green, int blue, int alpha = 255) noexcept
			:
			_r{ std::clamp(static_cast<uint8_t>(red  ), _min, _max) },
			_g{ std::clamp(static_cast<uint8_t>(green), _min, _max) },
			_b{ std::clamp(static_cast<uint8_t>(blue ), _min, _max) },
			_a{ std::clamp(static_cast<uint8_t>(alpha), _min, _max) }
		{
		}

		constexpr Color(float red, float green, float blue, float alpha = 1.0f) noexcept
			:
			_r{ std::clamp(static_cast<uint8_t>(red   * _max), _min, _max) },
			_g{ std::clamp(static_cast<uint8_t>(green * _max), _min, _max) },
			_b{ std::clamp(static_cast<uint8_t>(blue  * _max), _min, _max) },
			_a{ std::clamp(static_cast<uint8_t>(alpha * _max), _min, _max) }
		{
		}

		static constexpr Color Black()       noexcept { return Color(   0,   0,   0, 255); }
		static constexpr Color White()       noexcept { return Color( 255, 255, 255, 255); }
		static constexpr Color Red()         noexcept { return Color( 255,   0,   0, 255); }
		static constexpr Color Green()       noexcept { return Color(   0, 255,   0, 255); }
		static constexpr Color Blue()        noexcept { return Color(   0,   0, 255, 255); }
		static constexpr Color Cyan()        noexcept { return Color(   0, 255, 255, 255); }
		static constexpr Color Magenta()     noexcept { return Color( 255,   0, 255, 255); }
		static constexpr Color Yellow()      noexcept { return Color( 255, 255,   0, 255); }
		static constexpr Color Transparent() noexcept { return Color(   0,   0,   0,   0); }

		constexpr Color operator+=(const Color& color) noexcept
		{
			_r = std::clamp(static_cast<uint8_t>(_r + color._r), _min, _max);
			_g = std::clamp(static_cast<uint8_t>(_g + color._g), _min, _max);
			_b = std::clamp(static_cast<uint8_t>(_b + color._b), _min, _max);
			_a = std::clamp(static_cast<uint8_t>(_a + color._a), _min, _max);

			return *this;
		}

		constexpr Color operator*=(float scalar) noexcept
		{
			_r = std::clamp(static_cast<uint8_t>(_r * scalar), _min, _max);
			_g = std::clamp(static_cast<uint8_t>(_g * scalar), _min, _max);
			_b = std::clamp(static_cast<uint8_t>(_b * scalar), _min, _max);
			_a = std::clamp(static_cast<uint8_t>(_a * scalar), _min, _max);

			return *this;
		}

	private:

		static constexpr auto _min = std::numeric_limits<uint8_t>::min();
		static constexpr auto _max = std::numeric_limits<uint8_t>::max();

		uint8_t _r{ 0   };
		uint8_t _g{ 0   };
		uint8_t _b{ 0   };
		uint8_t _a{ 255 };
	};

	constexpr Color operator+(const Color& color1, const Color& color2) noexcept
	{
		auto result{ color1 };
		result += color2;
		return result;
	}

	constexpr Color operator*(const Color& color, float scalar) noexcept
	{
		auto result{ color };
		result *= scalar;
		return result;
	}

	constexpr Color operator*(float scalar, const Color& color) noexcept
	{
		return color * scalar;
	}

}