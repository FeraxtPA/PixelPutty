#pragma once
#include "raylib.h"


namespace PuttyColor
{
	inline constexpr Color Black = { 26, 28, 44, 255 };
	inline constexpr Color Purple = { 93, 39, 93, 255 };
	inline constexpr Color Red = { 177, 62, 83, 255 };
	inline constexpr Color Orange = { 239, 125, 87, 255 };
	inline constexpr Color Yellow = { 255, 205, 117, 255 };
	inline constexpr Color LightGreen = { 167, 240, 112, 255 };
	inline constexpr Color Green = { 56, 183, 100, 255 };
	inline constexpr Color DarkGreen = { 37, 113, 121, 255 };
	inline constexpr Color DarkBlue = { 41, 54, 111, 255 };
	inline constexpr Color Blue = { 59, 93, 201, 255 };
	inline constexpr Color LightBlue = { 65, 166, 246, 255 };
	inline constexpr Color SkyBlue = { 115, 239, 247, 255 };
	inline constexpr Color White = { 244, 244, 244, 255 };
	inline constexpr Color Grey = { 148, 176, 194, 255 };
	inline constexpr Color DarkGray = { 86, 108, 134, 255 };
	inline constexpr Color DarkestGray = { 51, 60, 87, 255 };



	inline Color SetAlpha(Color baseColor, unsigned int alpha)
	{
		baseColor.a = alpha;
		return baseColor;
	}
}