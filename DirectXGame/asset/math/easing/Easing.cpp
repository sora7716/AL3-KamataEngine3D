#include "Easing.h"

float Easing::In(float frame) {

	return 1 - cosf((frame * float(M_PI) / 2));
}

float Easing::Out(float frame) {
	return sinf((frame * float(M_PI)) / 2);
}

float Easing::InOut(float frame) {
	return -(cosf(float(M_PI) * frame) - 1) / 2;
}

float Easing::InBack(float frame) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return c3 * frame * frame * frame - c1 * frame * frame;
}

float Easing::outBack(float frame) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return float(1 + c3 * pow(frame - 1, 3) + c1 * pow(frame - 1, 2));
}