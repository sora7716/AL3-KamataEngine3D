#include "TitleAnimation.h"
#include "asset/gameObject/player/Player.h"
#include "asset/math/Math.h"
#include <cassert>
#include <numbers>
#define oneLap std::numbers::pi_v<float> * 2.0f
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

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
		BigAndSmall();
	}
	/*ImGui::Begin("animation");
	ImGui::*/
}

// 腕を回転させる
void TitleAnimation::ArmRotate() {

	static float begin = player_->GetPartsAngle(IPlayerParts::arm).y; // 最初の位置
	float end = oneLap * 3.0f;                                        // 最後の位置
	static float frame = 0.0f;                                        // フレーム
	float endFrame = 300.0f;                                          // エンドフレーム
	static bool isRotateReverse = false;                              // 逆回転
	static float result{};                                            // 結果
	// 一回目の回転
	if (frame++ > endFrame && !isRotateReverse) {
		frame = 0.0f;
		isRotateReverse = true;
	} else if (frame++ > endFrame && isRotateReverse) { // 二回目の回転
		frame = 0.0f;
		isRotateReverse = false;
		isAnimationStart = false;                 // アニメーションの開始フラグをリセット
		animationStartTimer = kAnimationInterval; // アニメーションタイマーをリセット
	}
	if (!isRotateReverse) {
		result = Math::Lerp(begin, end, Easing::OutBack(frame / endFrame)); // 線形補間
	} else if (isRotateReverse) {
		result = Math::Lerp(end, begin, Easing::OutBack(frame / endFrame)); // 線形補間
	}
	player_->SetPartsAngle(IPlayerParts::arm, Vector3(0.0f, result, 0.0f)); // アングルをセット
}

// 大きくなったり小さくなったりする
void TitleAnimation::BigAndSmall() {
	static float beginScale = 1.0f;
	float endScale = 3.0f;
	static float frame = 0.0f;
	static float endFrame = 300.0f;
	static float result = 0.0f;
	static bool isBig = true;
	static bool isLookAround = false;
	static bool isSmall = false;
	if (frame++ > endFrame) {
		if (isBig) {
			frame = 0.0f;
			isBig = false;
			isLookAround = true;
		}else if (isSmall&&!isLookAround) {
			isSmall = false;
			isBig = true;
			frame = 0.0f;
			isAnimationStart = false;                 // アニメーションの開始フラグをリセット
			animationStartTimer = kAnimationInterval; // アニメーションタイマーをリセット
		}
		if (!isLookAround) {
			isSmall = true;
			frame = 0.0f;
		}
	}
	if (isBig) {
	result = Math::Lerp(beginScale, endScale, frame / endFrame);
	} else if (isSmall) {
		result = Math::Lerp(endScale,beginScale , frame / endFrame);
	}
	player_->SetScale({result, result, result});
	LookAround(isLookAround);
}

void TitleAnimation::LookAround(bool& isStart) {
	static float rightAngleY = 1.0f;
	static float middleAngleY = 1.5f;
	static float leftAngleY = 2.0f;
	static float frame = 0.0f;
	static float endFrame = 120.0f;
	static float result = 0.0f;
	static float isRight = true;
	static bool isLeft = false;
	static bool isUndo = false;
	if (isStart) {
		if (frame++ > endFrame) {
			if (isRight) {
				frame = 0.0f;
				isRight = false;
				isLeft = true;
			} else if (isLeft) {
				frame = 0.0f;
				isLeft = false;
				isUndo = true;
			} else if (isUndo) {
				isUndo = false;
				isRight = true;
				isStart = false;
				frame = 0.0f;
			}
		}
		if (isRight) {
			result = Math::Lerp(middleAngleY, rightAngleY, frame / endFrame);
		} else if (isLeft) {
			result = Math::Lerp(rightAngleY, leftAngleY, frame / endFrame);
		} else if (isUndo) {
			result = Math::Lerp(leftAngleY, middleAngleY, frame / endFrame);
		}
		player_->SetPartsAngle(IPlayerParts::head, {0.0f, result, 0.0f});
	}
}
