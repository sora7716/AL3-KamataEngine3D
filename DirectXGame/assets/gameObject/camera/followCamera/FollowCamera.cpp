#include "FollowCamera.h"
#include "WorldTransform.h"
#include "assets/math/Math.h"
#include "input/Input.h"

// 初期化
void FollowCamera::Initialize() { viewProjection_.Initialize(); }

// 更新
void FollowCamera::Update() {
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};
		Matrix4x4 rotateMat = Math::MakeRotateXYZMatrix(viewProjection_.rotation_);
		offset = Math::TransformNormal(offset, rotateMat);
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = target_->translation_ + offset;
	}

	viewProjection_.UpdateMatrix();
}

// 追従対象のセッター
void FollowCamera::SetTarget(const WorldTransform* target) { target_ = target; }

// ビュープロジェクションのゲッター
ViewProjection& FollowCamera::GetViewProjection() { return viewProjection_; }

// ゲームパッドの操作
void FollowCamera::GamepadControl() {
	// ゲームパッド
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 回転速度
		const float rot = -0.000004f;
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX * rot;
	}
}

// キーボードの操作
void FollowCamera::KeyboardControl() {
	const float rot = 0.05f;
	float move = 0.0f;
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		move = -1.0f;
	} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		move = 1.0f;
	}
	move = Math::Normalize(move) * rot;
	viewProjection_.rotation_.y += move;
}
