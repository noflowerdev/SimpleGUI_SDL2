#pragma once

#include <cmath>
#include <corecrt_math_defines.h>

struct vec2
{
public:
	float x = 0, y = 0;
	vec2(float x, float y) : x(x), y(y) {}
	vec2(void) {}
	~vec2(void) {}

	vec2 operator+(vec2 v)
	{
		return vec2(x + v.x, y + v.y);
	}
	vec2 operator-(vec2 v)
	{
		return vec2(x - v.x, y - v.y);
	}
	vec2 operator*(vec2 v) {
		return vec2(x * v.x, y * v.y);
	}
	vec2 operator/(vec2 v)
	{
		return vec2(x / v.x, y / v.y);
	}
	float length(void)
	{
		return sqrtf(x * x + y * y);
	}
};

namespace miniMath
{
	inline float deg2rad(float deg)
	{
		return deg * static_cast<float>(M_PI) / 180.0f;
	}
	inline float rad2deg(float rad)
	{
		return rad * 180.0f / static_cast<float>(M_PI);
	}
	inline float dot(vec2 A, vec2 B)
	{
		return A.x * B.x + A.y * B.y;
	}
	inline float dotInv(vec2 A, vec2 B)
	{
		return A.x * B.y - A.y * B.x;
	}
	inline float angle_between(vec2 A, vec2 B)
	{
		if (dot(A, B) == 0 && dotInv(A, B) > 0) return static_cast<float>(M_PI) / 2.0f;
		else if (dot(A, B) == 0 && dotInv(A, B) < 0) return static_cast<float>(M_PI) / 2.0f * (-1.0f);
		else if (dot(A, B) > 0) return atan(dotInv(A, B) / dot(A, B));
		else if (dot(A, B) < 0 && dotInv(A, B) >= 0) return static_cast<float>(M_PI) / 2.0f + static_cast<float>(M_PI);
		else if (dot(A, B) < 0 && dotInv(A, B) < 0) return static_cast<float>(M_PI) / 2.0f - static_cast<float>(M_PI);
	}

}