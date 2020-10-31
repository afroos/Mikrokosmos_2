module;

#include <cstdint>
#include <cstddef>

export module Mikrokosmos_Graphics_Color;

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

		static constexpr Color Black()       { return Color{   0,   0,   0 }; }
		static constexpr Color White()       { return Color{ 255, 255, 255 }; }
		static constexpr Color Red()         { return Color{ 255,   0,   0 }; }
		static constexpr Color Green()       { return Color{   0, 255,   0 }; }
		static constexpr Color Blue()        { return Color{   0,   0, 255 }; }
		static constexpr Color Cyan()        { return Color{   0, 255, 255 }; }
		static constexpr Color Magenta()     { return Color{ 255,   0, 255 }; }
		static constexpr Color Yellow()      { return Color{ 255, 255,   0 }; }
		static constexpr Color Transparent() { return Color{   0,   0,   0,   0 }; }

	private:

		uint8_t _r{   0 };
		uint8_t _g{   0 };
		uint8_t _b{   0 };
		uint8_t _a{ 255 };
	};

}