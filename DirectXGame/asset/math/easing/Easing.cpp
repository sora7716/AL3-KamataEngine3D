#include "Easing.h"
#include <cmath>
#include <numbers>
using namespace std;
using namespace std::numbers;

// イン
float Easing::InSine(float frame) { return 1 - cosf((frame * float(M_PI) / 2)); }

// アウト
float Easing::OutSine(float frame) { return sinf((frame * float(M_PI)) / 2); }

// インアウト
float Easing::InOutSine(float frame) { return -(cosf(float(M_PI) * frame) - 1) / 2; }

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

// アウトエラスティック
float Easing::OutElastic(float frame) {
	const float c4 = (2 * pi_v<float>) / 3;
	if (frame == 0) {
		return 0;
	} else if (frame == 1) {
		return 1;
	} else {
		return powf(2, -10 * frame) * sinf((frame * 10.0f - 0.75f) * c4) + 1.0f;
	}
}

// インエクスポ
float Easing::InExpo(float frame) { return (frame == 0.0f) ? 0.0f : std::pow(2.0f, 10.0f * frame - 10.0f); }

// インアウトエクスポ
float Easing::InOutExpo(float frame) {
	if (frame == 0.0f) {
		return 0.0f;
	} else if (frame == 1.0f) {
		return 1.0f;
	} else if (frame < 0.5f) {
		return std::pow(2.0f, 20.0f * frame - 10.0f) / 2.0f;
	} else {
		return (2.0f - std::pow(2.0f, -20.0f * frame + 10.0f)) / 2.0f;
	}
}

// インアウトバック
float Easing::InOutBack(float frame) {
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	if (frame < 0.5f) {
		return (std::pow(2.0f * frame, 2.0f) * ((c2 + 1.0f) * 2.0f * frame - c2)) / 2.0f;
	} else {
		return (std::pow(2.0f * frame - 2.0f, 2.0f) * ((c2 + 1.0f) * (2.0f * frame - 2.0f) + c2) + 2.0f) / 2.0f;
	}
}

// アウトバウンス
float Easing::OutBounce(float frame) {
	if (frame < 1 / 2.75f) {
		return 7.5625f * frame * frame;
	} else if (frame < 2 / 2.75f) {
		frame -= 1.5f / 2.75f;
		return 7.5625f * frame * frame + 0.75f;
	} else if (frame < 2.5f / 2.75f) {
		frame -= 2.25f / 2.75f;
		return 7.5625f * frame * frame + 0.9375f;
	} else {
		frame -= 2.625f / 2.75f;
		return 7.5625f * frame * frame + 0.984375f;
	}
}

// インアウトバウンス
float Easing::InOutBounce(float frame) {
	if (frame < 0.5f) {
		return (1.0f - OutBounce(1.0f - 2.0f * frame)) / 2.0f;
	} else {
		return (1.0f + OutBounce(2.0f * frame - 1.0f)) / 2.0f;
	}
}

float Easing::InOutQuart(float frame) {
	if (frame < 0.5f) {
		return 8.0f * frame * frame * frame * frame;
	} else {
		return 1.0f - std::pow(-2.0f * frame + 2.0f, 4.0f) / 2.0f;
	}
}

// インアウトシーク
float Easing::InOutCirc(float frame) {
	if (frame < 0.5f) {
		return (1.0f - std::sqrt(1.0f - std::pow(2.0f * frame, 2.0f))) / 2.0f;
	} else {
		return (std::sqrt(1.0f - std::pow(-2.0f * frame + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}
}