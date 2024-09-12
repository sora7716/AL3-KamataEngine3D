#include "ISelectButton.h"
#include "asset/scene/title/select/Select.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// ボタンの線形補間
void ISelectButton::ButtonLerp() {
	static float beginX = -40.0f;
	float endY = -3.0f;
	float beginZ = 30.0f;
	float endZ = 10.0f;
	float endFrame = Select::kEndFrame;
	if (isButtonLerp_ && frame_ >= endFrame) {
		isButtonBack_ = true;
	}
	if (isButtonLerp_) {
		worldTransform_.translation_.x = Math::Lerp(beginX, endY, Easing::OutSine(frame_ / endFrame));
		worldTransform_.translation_.z = Math::Lerp(beginZ, endZ, Easing::OutSine(frame_ / endFrame));
	} else if (isButtonBack_) {
		worldTransform_.translation_.x = Math::Lerp(endY, beginX, Easing::OutSine(frame_ / endFrame));
		worldTransform_.translation_.z = Math::Lerp(endZ, beginZ, Easing::OutSine(frame_ / endFrame));
	}
}

// ボタンの線形補間フラグのセッター
void ISelectButton::SetIsButtonLarp(bool isButtonLarp) { isButtonLerp_ = isButtonLarp; }

// フレーム
void ISelectButton::SetFrame(float frame) { frame_ = frame; }
