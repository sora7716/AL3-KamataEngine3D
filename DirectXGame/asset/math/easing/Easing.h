#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
class Easing
{
public:
	static float In(float frame);

	static float Out(float frame);

	static float InOut(float frame);

	static float InBack(float frame);

	static float outBack(float frame);
};

