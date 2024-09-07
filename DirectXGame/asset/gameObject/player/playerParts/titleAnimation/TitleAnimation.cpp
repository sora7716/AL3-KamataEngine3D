#include "TitleAnimation.h"
#include "asset/gameObject/player/Player.h"
#include "asset/math/Math.h"
#include <cassert>
#include <numbers>
#define oneLap std::numbers::pi_v<float> * 2.0f

// 初期化
void TitleAnimation::Initialize(Player* player) {
	// Nullチェック
	assert(player);
	player_ = player; // プレイヤーを受け取る
	animationStartTimer = kAnimationInterval;
}

// 更新
void TitleAnimation::Update() {
	if (animationStartTimer-- < 0) {
		isAnimationStart = true;
	}
	if (isAnimationEnd) {
		animationStartTimer = kAnimationInterval; // 時間を元に戻す
	}
	if (isAnimationStart) {
		// アニメーション
		ArmRotate();
	}
}

// 腕を回転させる
void TitleAnimation::ArmRotate() {

	static float begin = player_->GetPartsAngle(IPlayerParts::arm).y; // 最初の位置
	float end = oneLap * 3.0f;                                        // 最後の位置
	static float frame = 0.0f;
	float endFrame = 120;
	if (frame++ > endFrame) {
		frame = endFrame;
	}
	float result = Math::Lerp(begin, end, Easing::OutBack(frame / endFrame));
	player_->SetPartsAngle(IPlayerParts::arm, Vector3(0.0f, result, 0.0f));
}
