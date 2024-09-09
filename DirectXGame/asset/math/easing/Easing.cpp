#include "Easing.h"
#include <cmath>
#include <numbers>
using namespace std;
using namespace std::numbers;

// イン
float Easing::In(float frame) { return 1 - cosf((frame * float(M_PI) / 2)); }

// アウト
float Easing::Out(float frame) { return sinf((frame * float(M_PI)) / 2); }

// インアウト
float Easing::InOut(float frame) { return -(cosf(float(M_PI) * frame) - 1) / 2; }

// インバック
float Easing::InBack(float frame) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return c3 * frame * frame * frame - c1 * frame * frame;
}

// アウトバック
float Easing::OutBack(float frame) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return float(1 + c3 * pow(frame - 1, 3) + c1 * pow(frame - 1, 2));
}

// イーズアウトエラスティック
float Easing::EaseOutElastic(float frame) {
	const float c4 = (2 * pi_v<float>) / 3;
	if (frame == 0) {
		return 0;
	} else if (frame == 1) {
		return 1;
	} else {
		return powf(2, -10 * frame) * sinf((frame * 10.0f - 0.75f) * c4) + 1.0f;
	}
}
