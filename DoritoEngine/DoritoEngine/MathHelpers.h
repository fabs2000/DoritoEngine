#pragma once
#include "DoritoPCH.h"

#define DOR_PI 3.14159265359f
#define DOR_EP 0.0000001f

namespace DoritoMath
{
	inline float RadiansToDegrees(float angle)
	{
		float degrees = angle * (180.f / DOR_PI);

		return degrees;
	}

	inline float DegreesToRadians(float angle)
	{
		float radians = angle * (DOR_PI / 180.f);

		return radians;
	}

	inline bool FEquals(float a, float b, float precision = DOR_EP)
	{
		if (fabs(a - b) < precision)
			return true;

		return false;
	}

	inline bool VecEquals(const sf::Vector2f& vec, const sf::Vector2f& other)
	{
		return FEquals(vec.x, other.x) && FEquals(vec.y, other.y);
	}

	inline float Magnitude(const sf::Vector2f& vec)
	{
		return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
	}

	inline const sf::Vector2f& Normalize(sf::Vector2f& vec)
	{
		if (FEquals(Magnitude(vec), 0.f))
			return vec;

		float m = Magnitude(vec);

		vec.x /= m;
		vec.y /= m;

		return vec;
	}

	//LERP FUNCTION
	//https://stackoverflow.com/questions/4353525/floating-point-linear-interpolation
	inline float Lerp(float begin, float end, float factor)
	{
		return begin + factor * (end - begin);
	}

	//TAKEN FROM OVERLORD
	inline float RandF(float min, float max)
	{
		const float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		const float diff = max - min;
		const float r = random * diff;
		return min + r;
	}

	inline int Rand(int min, int max)
	{
		int num = (rand() % (max - min + 1)) + min;

		return num;
	}

	inline float Square(float val)
	{
		return val * val;
	}

	inline float SquareDistance(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return Square(v2.x - v1.x) + Square(v2.y - v1.y);
	}

}