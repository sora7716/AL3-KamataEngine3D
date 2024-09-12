#include "TitleAnimation.h"
#include "asset/gameObject/player/Player.h"
#include "asset/math/Math.h"
#include <cassert>
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void TitleAnimation::Initialize(Player* player) {
	// Nullチェック
	assert(player);
	player_ = player;                          // プレイヤーを受け取る
	animationStartTimer_ = kAnimationInterval; // アニメーションを開始するまでの時間の設定
	idolAnimationFrame_ = 0.0f;                             // フレームの再設定
}

// 更新
void TitleAnimation::Update(bool isHome) {
	if (!isHome) { // ホームじゃなかったらアニメーションを終わらせる
		isAnimationEnd_ = true;
		idolAnimationFrame_ = 0.0f; // フレーム数をリセット
	}
	if (animationStartTimer_-- < 0) {
		isAnimationStart_ = true; // タイマーがゼロになったらアニメーション開始
	}
	if (isAnimationEnd_) { // アニメーションが終わったら
		if (!isHome) {
			animationStartTimer_ = 60;
		} else {
			animationStartTimer_ = kAnimationInterval; // 時間を元に戻す
		}
		isAnimationEnd_ = false;   // アニメーション終了フラグをfalse
		isAnimationStart_ = false; // アニメーション開始フラグをfalse
		idolAnimationFrame_ = 0.0f;             // フレームを戻す
		// アニメーションの番号を加算していき最大数を超えたら0に戻す
		if (animationNumber_ >= kAnimationMaximumNumber - 1) {
			animationNumber_ = 0;
		} else {
			animationNumber_++;
		}
	} else if (isAnimationStart_) {
		animationStartTimer_ = 0;
		// アニメーション
		//(this->*animationTable[animationNumber_])();
	}
#ifdef _DEBUG
	ImGui::Begin("animation");
	ImGui::Text("animation:%d", animationStartTimer_);
	ImGui::Text("animationNumber:%d", animationNumber_);
	ImGui::End();
#endif // _DEBUG
}

void (TitleAnimation::*TitleAnimation::animationTable[])() = {
    &ArmRotate,
    &BigAndSmall,
    &ArmDrop,
};

#pragma region アニメーション
// 腕を回転させる
void TitleAnimation::ArmRotate() {

	static float begin = player_->GetPartsAngle(IPlayerParts::arm).y; // 最初の位置
	float end = oneLap * 3.0f;                                        // 最後の位置
	float endFrame = 300.0f;                                          // エンドフレーム
	static bool isRotateReverse = false;                              // 逆回転
	static float result{};                                            // 結果
	if (isAnimationEnd_) {                                            // フラグをリセット
		isRotateReverse = false;
	}
	// 一回目の回転
	if (idolAnimationFrame_++ > endFrame) {
		if (!isRotateReverse) {
			idolAnimationFrame_ = 0.0f;
			isRotateReverse = true;
		} else if (isRotateReverse) { // 二回目の回転
			idolAnimationFrame_ = 0.0f;
			isRotateReverse = false;
			isAnimationEnd_ = true; // アニメーション終了フラグをtrue
		}
	}
	if (!isRotateReverse) {
		result = Math::Lerp(begin, end, Easing::InOutQuart(idolAnimationFrame_ / endFrame)); // 線形補間
	} else if (isRotateReverse) {
		result = Math::Lerp(end, begin, Easing::InOutQuart(idolAnimationFrame_ / endFrame)); // 線形補間
	}
	player_->SetPartsAngle(IPlayerParts::arm, Vector3(0.0f, result, 0.0f)); // アングルをセット
}

// 大きくなったり小さくなったりする
void TitleAnimation::BigAndSmall() {
	float beginScale = 1.0f;          // 最初のスケール
	float endScale = 3.0f;            // 最後のスケール
	float endFrame = 300.0f;          // 最後のフレーム
	static float result = 0.0f;       // 結果を入れる
	static bool isBig = true;         // 大きくなる時のフラグ
	static bool isLookAround = false; // 見回すときのフレーム
	static bool isSmall = false;      // 小さくなる時のフレーム
	if (isAnimationEnd_) {            // フラグをリセット
		isBig = true;
		isLookAround = false;
		isSmall = false;
	}
	if (idolAnimationFrame_++ > endFrame) {
		if (isBig) { // 大きくなりっ来た時の処理
			idolAnimationFrame_ = 0.0f;
			isBig = false;
			isLookAround = true;
		} else if (isSmall && !isLookAround) { // 最後に元の大きさに戻った時の処理
			isSmall = false;
			isBig = true;
			idolAnimationFrame_ = 0.0f;
			isAnimationEnd_ = true; // アニメーション終了フラグをtrue
		}
		if (!isLookAround && !isBig) { // 見回すときの処理
			isSmall = true;
			idolAnimationFrame_ = 0.0f;
		}
	}
	if (isBig) { // 大きくなっているときの線形補間
		result = Math::Lerp(beginScale, endScale, Easing::OutSine(idolAnimationFrame_ / endFrame));
	} else if (isSmall) { // 元の大きさに戻るときの線形補間
		result = Math::Lerp(endScale, beginScale, Easing::OutSine(idolAnimationFrame_ / endFrame));
	}
	player_->SetScale({result, result, result}); // スケールのセット
	LookAround(isLookAround);                    // 見回す
}

// 見回す
void TitleAnimation::LookAround(bool& isStart) {
	float rightAngleY = 1.0f;  // 右向く角度
	float middleAngleY = 1.5f; // 正面を向く角度
	float leftAngleY = 2.0f;   // 左を向く角度
	float endFrame = 120.0f;
	float result = 0.0f;
	static bool isRight = true; // 右向こうとしているときのフラグ
	static bool isLeft = false; // 左向こうとしているときのフラグ
	static bool isUndo = false; // 正面向こうとしているときのフラグ
	if (isAnimationEnd_) {      // フラグをリセット
		isRight = true;
		isLeft = false;
		isUndo = false;
	}
	if (isStart) {
		if (idolAnimationFrame_++ > endFrame) {
			if (isRight) { // 右向いているときの処理
				idolAnimationFrame_ = 0.0f;
				isRight = false;
				isLeft = true;
			} else if (isLeft) { // 左向いているときの処理
				idolAnimationFrame_ = 0.0f;
				isLeft = false;
				isUndo = true;
			} else if (isUndo) { // 元の正面向いているときの処理
				isUndo = false;
				isRight = true;
				isStart = false;
				idolAnimationFrame_ = 0.0f;
			}
		}
		if (isRight) { // 右向いているときの線形補間
			result = Math::Lerp(middleAngleY, rightAngleY, Easing::InOutExpo(idolAnimationFrame_ / endFrame));
		} else if (isLeft) { // 左向いているときの線形補間
			result = Math::Lerp(rightAngleY, leftAngleY, Easing::InOutExpo(idolAnimationFrame_ / endFrame));
		} else if (isUndo) { // 正面向いているときの線形補間
			result = Math::Lerp(leftAngleY, middleAngleY, Easing::InOutExpo(idolAnimationFrame_ / endFrame));
		}
		player_->SetPartsAngle(IPlayerParts::head, {0.0f, result, 0.0f}); // アングルをセット
	}
}

// 腕を落とす
void TitleAnimation::ArmDrop() {
	static float leftBegin = player_->GetPartsPosition(IPlayerParts::left_arm).y;   // 左の最初の位置
	static float rightBegin = player_->GetPartsPosition(IPlayerParts::right_arm).y; // 右の最初の位置
	float armEnd = -8.0f;                                                           // 最終的に行きつく場所
	static float leftResult = 0.0f;                                                 // 左の結果
	static float rightResult = 0.0f;                                                // 右の結果
	float endFrame = 120;                                                           // 最後のフレーム数
	static bool isLeftDrop = true;                                                  // 左を落とす
	static bool isRightDrop = false;                                                // 右を落とす
	static bool isUndoLeft = false;                                                 // 左を戻す
	static bool isUndoRight = false;                                                // 右を戻す
	static bool isLookDown = false;                                                 // 少し待つ時間のフラグ
	if (isAnimationEnd_) {                                                          // フラグをリセット
		isLeftDrop = true;
		isRightDrop = false;
		isUndoLeft = false;
		isUndoRight = false;
		isLookDown = false;
	}
	if (idolAnimationFrame_++ > endFrame) {
		if (isLeftDrop) { // 左腕を落とし終わったとき
			idolAnimationFrame_ = 0.0f;
			isLeftDrop = false;
			isRightDrop = true;
		} else if (isRightDrop) { // 右腕を落とし終わったとき
			idolAnimationFrame_ = 0.0f;
			isRightDrop = false;
			isLookDown = true;
		} else if (isUndoLeft) { // 左腕を拾いに行くとき
			idolAnimationFrame_ = 0.0f;
			isUndoLeft = false;
			isUndoRight = true;
		}
	}

	// 下を見る
	LookDown(isLookDown, isUndoLeft, isUndoRight, isLeftDrop);

	if (isLeftDrop) { // 左腕を落とすための線形補間
		leftResult = Math::Lerp(leftBegin, armEnd, Easing::OutBounce(idolAnimationFrame_ / endFrame));
	} else if (isRightDrop) { // 右腕を落とすための線形補間
		rightResult = Math::Lerp(rightBegin, armEnd, Easing::OutBounce(idolAnimationFrame_ / endFrame));
	} else if (isUndoLeft) { // 左腕を拾うための線形補間
		leftResult = Math::Lerp(armEnd, leftBegin, Easing::OutBack(idolAnimationFrame_ / endFrame));
	} else if (isUndoRight) { // 右腕を拾うための線形補間
		rightResult = Math::Lerp(armEnd, rightBegin, Easing::OutBack(idolAnimationFrame_ / endFrame));
	}
	player_->SetPartsPosition(IPlayerParts::left_arm, {0.0f, leftResult, 2.0f});    // 位置をセット
	player_->SetPartsPosition(IPlayerParts::right_arm, {0.0f, rightResult, -2.0f}); // 位置をセット
}

// 下を見る
void TitleAnimation::LookDown(bool& isLookDown, bool& isUndoLeft, bool& isUndoRight, bool& isLeftDrop) {
	float begin = 0.0f;           // 最初の角度
	float end = -0.6f;            // 最後の角度
	float endFrame = 120;         // 最後のフレーム
	static float result = 0.0f;   // 結果を格納
	static bool isLookUp = false; // 上を見るフラグ
	if (isAnimationEnd_) {        // フラグをリセット
		isLookUp = false;
	}
	if (idolAnimationFrame_++ > endFrame) {
		if (isLookDown) { // 下を見終わったとき
			idolAnimationFrame_ = 0.0f;
			isLookDown = false;
			isUndoLeft = true;
		} else if (isUndoRight) { // 右腕を広い終わった時
			idolAnimationFrame_ = 0.0f;
			isUndoRight = false;
			isLookUp = true;
		} else if (isLookUp) {
			idolAnimationFrame_ = 0.0f;
			isLookUp = false;
			isLeftDrop = true;
			isAnimationEnd_ = true;
		}
	}
	if (isLookDown) { // 下を見るときの線形補間
		result = Math::Lerp(begin, end, Easing::InSine(idolAnimationFrame_ / endFrame));
	} else if (isLookUp) { // 上を見るときの線形補間
		result = Math::Lerp(end, begin, Easing::OutSine(idolAnimationFrame_ / endFrame));
	}
	player_->SetPartsAngle(IPlayerParts::head, {result, player_->GetPartsAngle(IPlayerParts::head).y, 0.0f}); // 頭の角度を設定
}

void TitleAnimation::FallDown() {}

#pragma endregion
