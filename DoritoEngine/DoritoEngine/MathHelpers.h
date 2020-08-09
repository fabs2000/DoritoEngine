#pragma once
#include "DoritoPCH.h"

#define DOR_PI 3.14159265359f
#define DOR_EP 0.0001f

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

	inline bool VecEquals(const sf::Vector2f& vec, const sf::Vector2f& other)
	{
		return (fabs(vec.x - other.x) < DOR_EP) && (fabs(vec.y - other.y) < DOR_EP);
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
}