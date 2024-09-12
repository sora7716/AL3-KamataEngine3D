#include "TitleAnimation.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/player/Player.h"
#include "asset/math/Math.h"
#include <cassert>
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void TitleAnimation::Initialize(Player* player, RailCamera* camera) {
	// Nullチェック
	assert(player);
	player_ = player;                          // プレイヤーを受け取る
	assert(camera);                            // Nullチェック
	camera_ = camera;                          // カメラを受け取る
	animationStartTimer_ = kAnimationInterval; // アニメーションを開始するまでの時間の設定
	animationFrame_ = 0.0f;                    // フレームの再設定
}

// 更新
void TitleAnimation::Update(bool isHome) {
	if (!isHome) { // ホームじゃなかったらアニメーションを終わらせる
		isAnimationEnd_ = true;
		animationFrame_ = 0.0f; // フレーム数をリセット
	}
	if (animationStartTimer_-- < 0) {
		isAnimationStart_ = true; // タイマーがゼロになったらアニメーション開始
	}
	if (isAnimationEnd_) { // アニメーションが終わったら
		if (!isHome) {
			animationStartTimer_ = 180;
		} else {
			animationStartTimer_ = kAnimationInterval; // 時間を元に戻す
		}
		isAnimationEnd_ = false;   // アニメーション終了フラグをfalse
		isAnimationStart_ = false; // アニメーション開始フラグをfalse
		animationFrame_ = 0.0f;    // フレームを戻す
		// アニメーションの番号を加算していき最大数を超えたら0に戻す
		if (animationNumber_ >= kAnimationMaximumNumber - 1) {
			animationNumber_ = 0;
		} else {
			animationNumber_++;
		}
	} else if (isAnimationStart_) {
		animationStartTimer_ = 0;
		if (!isGameStartAnimation_) {
			// アニメーション
			(this->*animationTable[animationNumber_])();
		}
	}
	if (isGameStartAnimation_) {
		FallDown();
		player_->SetScale({1.0f, 1.0f, 1.0f});
		// プレイヤーのスケールを調整
		// 位置
		player_->SetPartsPosition(IPlayerParts::left_ear, {-1.5f, 0.0f, 0.0f}); // 左耳
		player_->SetPartsPosition(IPlayerParts::right_ear, {1.5f, 0.0f, 0.0f}); // 右耳
		                                                                        // 角度
		player_->SetPartsAngle(IPlayerParts::left_ear, {0.0f, 0.0f, 0.0f});     // 左耳
		player_->SetPartsAngle(IPlayerParts::right_ear, {0.0f, 0.0f, 0.0f});    // 右耳
	}
#ifdef _DEBUG
	ImGui::Begin("animation");
	ImGui::Text("animation:%d", animationStartTimer_);
	ImGui::Text("animationNumber:%d", animationNumber_);
	ImGui::Checkbox("isGameStartAnimation", &isGameStartAnimation_);
	ImGui::Checkbox("isCameraMove", &isCameraMove_);
	ImGui::Checkbox("isPlayerMove", &isPlayerMove_);
	ImGui::End();
#endif // _DEBUG
}

void (TitleAnimation::*TitleAnimation::animationTable[])() = {
    &ArmRotate,
    &BigAndSmall,
    &ArmDrop,
};

#pragma region 待機アニメーション
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
	if (animationFrame_++ > endFrame) {
		if (!isRotateReverse) {
			animationFrame_ = 0.0f;
			isRotateReverse = true;
		} else if (isRotateReverse) { // 二回目の回転
			animationFrame_ = 0.0f;
			isRotateReverse = false;
			isAnimationEnd_ = true; // アニメーション終了フラグをtrue
		}
	}
	if (!isRotateReverse) {
		result = Math::Lerp(begin, end, Easing::InOutQuart(animationFrame_ / endFrame)); // 線形補間
	} else if (isRotateReverse) {
		result = Math::Lerp(end, begin, Easing::InOutQuart(animationFrame_ / endFrame)); // 線形補間
	}
	player_->SetPartsAngle(IPlayerParts::arm, Vector3(0.0f, result, 0.0f)); // アングルをセット
}

// 大きくなったり小さくなったりする
void TitleAnimation::BigAndSmall() {
	float beginScale = 1.0f;          // 最初のスケール
	float endScale = 3.0f;            // 最後のスケール
	float endFrame = 180.0f;          // 最後のフレーム
	static float result = 0.0f;       // 結果を入れる
	static bool isBig = true;         // 大きくなる時のフラグ
	static bool isLookAround = false; // 見回すときのフレーム
	static bool isSmall = false;      // 小さくなる時のフレーム
	if (isAnimationEnd_) {            // フラグをリセット
		isBig = true;
		isLookAround = false;
		isSmall = false;
	}
	if (animationFrame_++ > endFrame) {
		if (isBig) { // 大きくなりっ来た時の処理
			animationFrame_ = 0.0f;
			isBig = false;
			isLookAround = true;
		} else if (isSmall && !isLookAround) { // 最後に元の大きさに戻った時の処理
			isSmall = false;
			isBig = true;
			animationFrame_ = 0.0f;
			isAnimationEnd_ = true; // アニメーション終了フラグをtrue
		}
		if (!isLookAround && !isBig) { // 見回すときの処理
			isSmall = true;
			animationFrame_ = 0.0f;
		}
	}
	if (isBig) { // 大きくなっているときの線形補間
		result = Math::Lerp(beginScale, endScale, Easing::OutQuad(animationFrame_ / endFrame));
	} else if (isSmall) { // 元の大きさに戻るときの線形補間
		result = Math::Lerp(endScale, beginScale, Easing::OutBounce(animationFrame_ / endFrame));
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
		if (animationFrame_++ > endFrame) {
			if (isRight) { // 右向いているときの処理
				animationFrame_ = 0.0f;
				isRight = false;
				isLeft = true;
			} else if (isLeft) { // 左向いているときの処理
				animationFrame_ = 0.0f;
				isLeft = false;
				isUndo = true;
			} else if (isUndo) { // 元の正面向いているときの処理
				isUndo = false;
				isRight = true;
				isStart = false;
				animationFrame_ = 0.0f;
			}
		}
		if (isRight) { // 右向いているときの線形補間
			result = Math::Lerp(middleAngleY, rightAngleY, Easing::InOutExpo(animationFrame_ / endFrame));
		} else if (isLeft) { // 左向いているときの線形補間
			result = Math::Lerp(rightAngleY, leftAngleY, Easing::InOutExpo(animationFrame_ / endFrame));
		} else if (isUndo) { // 正面向いているときの線形補間
			result = Math::Lerp(leftAngleY, middleAngleY, Easing::InOutExpo(animationFrame_ / endFrame));
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
	if (animationFrame_++ > endFrame) {
		if (isLeftDrop) { // 左腕を落とし終わったとき
			animationFrame_ = 0.0f;
			isLeftDrop = false;
			isRightDrop = true;
		} else if (isRightDrop) { // 右腕を落とし終わったとき
			animationFrame_ = 0.0f;
			isRightDrop = false;
			isLookDown = true;
		} else if (isUndoLeft) { // 左腕を拾いに行くとき
			animationFrame_ = 0.0f;
			isUndoLeft = false;
			isUndoRight = true;
		}
	}

	// 下を見る
	LookDown(isLookDown, isUndoLeft, isUndoRight, isLeftDrop);

	if (isLeftDrop) { // 左腕を落とすための線形補間
		leftResult = Math::Lerp(leftBegin, armEnd, Easing::OutBounce(animationFrame_ / endFrame));
	} else if (isRightDrop) { // 右腕を落とすための線形補間
		rightResult = Math::Lerp(rightBegin, armEnd, Easing::OutBounce(animationFrame_ / endFrame));
	} else if (isUndoLeft) { // 左腕を拾うための線形補間
		leftResult = Math::Lerp(armEnd, leftBegin, Easing::OutBack(animationFrame_ / endFrame));
	} else if (isUndoRight) { // 右腕を拾うための線形補間
		rightResult = Math::Lerp(armEnd, rightBegin, Easing::OutBack(animationFrame_ / endFrame));
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
	if (animationFrame_++ > endFrame) {
		if (isLookDown) { // 下を見終わったとき
			animationFrame_ = 0.0f;
			isLookDown = false;
			isUndoLeft = true;
		} else if (isUndoRight) { // 右腕を広い終わった時
			animationFrame_ = 0.0f;
			isUndoRight = false;
			isLookUp = true;
		} else if (isLookUp) {
			animationFrame_ = 0.0f;
			isLookUp = false;
			isLeftDrop = true;
			isAnimationEnd_ = true;
		}
	}
	if (isLookDown) { // 下を見るときの線形補間
		result = Math::Lerp(begin, end, Easing::InSine(animationFrame_ / endFrame));
	} else if (isLookUp) { // 上を見るときの線形補間
		result = Math::Lerp(end, begin, Easing::OutSine(animationFrame_ / endFrame));
	}
	player_->SetPartsAngle(IPlayerParts::head, {result, player_->GetPartsAngle(IPlayerParts::head).y, 0.0f}); // 頭の角度を設定
}

#pragma endregion

void TitleAnimation::FallDown() {
	// エンドフレーム
	float endFrame = 300.0f;
	// カメラ
	static Vector3 beginCameraPos = camera_->GetWorldTransform().translation_;
	static Vector3 beginCameraAngle = camera_->GetWorldTransform().rotation_;
	Vector3 middleCameraPos = {18.0f, 1.8f, 30.0f};
	Vector3 endCameraPos = {0.5f, 3.2f, 50.0};
	Vector3 endCameraAngle = {0.0f, -std::numbers::pi_v<float>, 0.0f};
	static Vector3 resultCameraPos = {};
	static Vector3 resultCameraAngle = {};

	// プレイヤー
	static Vector3 beginPlayerPos = player_->GetWorldTransform().translation_;
	Vector3 middlePlayerPos = {5.0f, 4.0f, -20.0f};
	Vector3 endPlayerPos = {0.0f, -50.42f, -50.0f};
	static Vector3 beginPlayerAngle = player_->GetWorldTransform().rotation_;
	Vector3 middlePlayerAngle = {-1.6f, 0.03f, 1.56f};
	Vector3 endPlayerAngle = {-1.53f, -0.471f, 1.57f};
	static Vector3 resultPlayerAngle = player_->GetWorldTransform().rotation_;
	static Vector3 resultPlayerPos = player_->GetWorldTransform().translation_;
	// プレイヤーパーツ
	//  位置
	static Vector3 partsBeginPos[6] = {
	    {0.0f, 1.0f,   0.0f }, //  頭
	    {0.0f, -2.25f, 0.0f }, //  体
	    {0.0f, -0.98f, 0.0f }, //  腕
	    {0.0f, 0.0f,   2.0f }, //  左腕
	    {0.0f, 0.0f,   -2.0f}, //  右腕
	    {0.0f, 2.0f,   0.0f }, //  耳
	};
	static Vector3 partsEndPos[6] = {
	    {-2.59f, 0.54f,  0.0f }, //  頭
	    {0.0f,   -1.43f, 0.0f }, //  体
	    {-0.5f,  0.13f,  0.0f }, //  腕
	    {0.0f,   0.0f,   2.0f }, //  左腕
	    {0.0f,   0.0f,   -2.0f}, //  右腕
	    {-2.65f, 1.86f,  0.0f }  //  耳
	};
	static Vector3 partsResultPos[6] = {
	    {0.0f, 1.0f,   0.0f }, //  頭
	    {0.0f, -2.25f, 0.0f }, //  体
	    {0.0f, -0.98f, 0.0f }, //  腕
	    {0.0f, 0.0f,   2.0f }, //  左腕
	    {0.0f, 0.0f,   -2.0f}, //  右腕
	    {0.0f, 2.0f,   0.0f }, //  耳
	};
	// 角度
	static Vector3 partsBeginAngle[6] = {
	    {0.0f,  std::numbers::pi_v<float> / 2.0f, 0.0f}, //  頭
	    {0.0f,  0.0f,	                         0.0f}, //  体
	    {0.0f,  0.0f,	                         0.0f}, //  腕
	    {0.3f,  5.6f,	                         2.3f}, //  左腕
	    {-0.3f, -5.6f,	                        2.3f}, //  右腕
	    {1.0f,  1.5f,	                         0.0f}, //  耳
	};
	static Vector3 partsEndAngle[6] = {
	    {-0.49f, std::numbers::pi_v<float> / 2.0f, 0.0f }, //  頭
	    {0.0f,   0.0f,	                         1.13f}, //  体
	    {0.0f,   0.0f,	                         1.12f}, //  腕
	    {-1.41f, 5.6f,	                         1.53f}, //  左腕
	    {1.41f,  0.0f,	                         1.44f}, //  右腕
	    {1.0f,   1.5f,	                         0.0f }, //  耳
	};
	static Vector3 partsResultAngle[6] = {
	    {0.0f,  std::numbers::pi_v<float> / 2.0f, 0.0f}, //  頭
	    {0.0f,  0.0f,	                         0.0f}, //  体
	    {0.0f,  0.0f,	                         0.0f}, //  腕
	    {0.3f,  5.6f,	                         2.3f}, //  左腕
	    {-0.3f, -5.6f,	                        2.3f}, //  右腕
	    {1.0f,  1.5f,	                         0.0f}, //  耳
	};
	if (animationFrame_++ > endFrame) {
		isMoveGameScene_ = true;
		if (isCameraMove_) {
			animationFrame_ = 0.0f;
			isCameraMove_ = false;
			isPlayerMove_ = true;
		} else if (isPlayerMove_) {
			animationFrame_ = 0.0f;
			isPlayerMove_ = false;
			isChangeGameScene_ = true;
		}
	}
	if (isCameraMove_) { // カメラの移動
		// プレイヤーの初期化
		resultPlayerAngle = player_->GetWorldTransform().rotation_;
		resultPlayerPos = player_->GetWorldTransform().translation_;
		// 位置
		partsResultAngle[0] = {0.0f, std::numbers::pi_v<float> / 2.0f, 0.0f}; //  頭
		partsResultAngle[1] = {0.0f, 0.0f, 0.0f};                             //  体
		partsResultAngle[2] = {0.0f, 0.0f, 0.0f};                             //  腕
		partsResultAngle[3] = {0.3f, 5.6f, 2.3f};                             // 左腕
		partsResultAngle[4] = {-0.3f, -5.6f, 2.3f};                           // 右腕
		partsResultAngle[5] = {1.0f, 1.5f, 0.0f};                             // 耳
		// 角度
		partsResultPos[0] = {0.0f, 1.0f, 0.0f};   //  頭
		partsResultPos[1] = {0.0f, -2.25f, 0.0f}; //  体
		partsResultPos[2] = {0.0f, -0.98f, 0.0f}; //  腕
		partsResultPos[3] = {0.0f, 0.0f, 2.0f};   // 左腕
		partsResultPos[4] = {0.0f, 0.0f, -2.0f};  // 右腕
		partsResultPos[5] = {0.0f, 2.0f, 0.0f};   // 耳
		resultCameraPos = Math::BezierS(beginCameraPos, middleCameraPos, endCameraPos, animationFrame_ / endFrame);
		resultCameraAngle = Math::Lerp(beginCameraAngle, endCameraAngle, animationFrame_ / endFrame);
	} else if (isPlayerMove_) { // プイレイヤーの移動
		resultPlayerPos = Math::BezierS(beginPlayerPos, middlePlayerPos, endPlayerPos, Easing::InBack(animationFrame_ / endFrame));
		resultPlayerAngle = Math::BezierS(beginPlayerAngle, middlePlayerAngle, endPlayerAngle, Easing::InSine(animationFrame_ / endFrame));
		for (int i = 0; i < 6; i++) {
			partsResultPos[i] = Math::Lerp(partsBeginPos[i], partsEndPos[i], Easing::OutCirc(animationFrame_ / endFrame));
			partsResultAngle[i] = Math::Lerp(partsBeginAngle[i], partsEndAngle[i], Easing::OutCirc(animationFrame_ / endFrame));
		}
	}

	// 計算結果をセット
	camera_->SetTranslation(resultCameraPos);
	camera_->SetRotation(resultCameraAngle);
	player_->SetPosition(resultPlayerPos);
	player_->SetRotation(resultPlayerAngle);
	for (int i = 0; i < 6; i++) {
		player_->SetPartsPosition((IPlayerParts::Parts)i, partsResultPos[i]);
		player_->SetPartsAngle((IPlayerParts::Parts)i, partsResultAngle[i]);
	}
}