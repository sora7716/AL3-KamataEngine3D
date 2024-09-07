#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
class Easing
{
public:
	float In   (float frame);

	float Out  (float frame);

	float InOut(float frame);

	float InBack(float frame);

	float outBack(float frame);
};

