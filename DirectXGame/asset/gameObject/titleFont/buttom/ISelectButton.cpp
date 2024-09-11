#include "ISelectButton.h"
#include "asset/scene/title/select/Select.h"

// ボタンの線形補間
void ISelectButton::ButtonLerp() {
	static float begin = worldTransform_.translation_.x;
	float end = -3.0f;
	static bool isBack = false;
	float endFrame = Select::kEndFrame;
	if (isBottanLerp_ && frame_ >= endFrame) {
		isBack = true;
	}
	if (isBottanLerp_) {
		worldTransform_.translation_.x = Math::Lerp(begin, end, frame_ / endFrame);
	} else if (isBack) {
		worldTransform_.translation_.x = Math::Lerp(end, begin, frame_ / endFrame);
	}
}

// ボタンの線形補間フラグのセッター
void ISelectButton::SetIsBottonLarp(bool isBottonLarp) { isBottanLerp_ = isBottonLarp; }

// フレーム
void ISelectButton::SetFrame(float frame) { frame_ = frame; }
