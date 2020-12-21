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

		constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
			:
			_r{ r },
			_g{ g },
			_b{ b },
			_a{ a }
		{
		}

		static constexpr Color Black()       { return Color(   0,   0,   0, 255); }
		static constexpr Color White()       { return Color( 255, 255, 255, 255); }
		static constexpr Color Red()         { return Color( 255,   0,   0, 255); }
		static constexpr Color Green()       { return Color(   0, 255,   0, 255); }
		static constexpr Color Blue()        { return Color(   0,   0, 255, 255); }
		static constexpr Color Cyan()        { return Color(   0, 255, 255, 255); }
		static constexpr Color Magenta()     { return Color( 255,   0, 255, 255); }
		static constexpr Color Yellow()      { return Color( 255, 255,   0, 255); }
		static constexpr Color Transparent() { return Color(   0,   0,   0,   0); }

		constexpr Color operator+=(const Color& color)
		{
			_r = std::clamp(static_cast<uint8_t>(_r + color._r), _min, _max);
			_g = std::clamp(static_cast<uint8_t>(_g + color._g), _min, _max);
			_b = std::clamp(static_cast<uint8_t>(_b + color._b), _min, _max);
			_a = std::clamp(static_cast<uint8_t>(_a + color._a), _min, _max);

			return *this;
		}

		constexpr Color operator*=(float scalar)
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

	constexpr Color operator+(const Color& color1, const Color& color2)
	{
		auto result{ color1 };
		result += color2;
		return result;
	}

	constexpr Color operator*(const Color& color, float scalar)
	{
		auto result{ color };
		result *= scalar;
		return result;
	}

}