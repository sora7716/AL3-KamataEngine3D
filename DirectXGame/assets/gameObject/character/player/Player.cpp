#include "Player.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include "input/Input.h"
#include <cassert>
// 初期化
void Player::Initialize(ViewProjection* viewProjection, Model* model) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

// 更新
void Player::Update() {

	// ゲームパッドの操作
	GamePadControl();

	// キーボードの操作
	KeyBoaeredControl();

	// 移動量に速さを反映
	if (isMove_) {
		move_ = Math::Normalize(move_) * speed_;
		Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
		move_ = Math::TransformNormal(move_, rotMat);
		// Y軸周りの角度(θy)
		worldTransform_.rotation_.y = atan2(move_.x, move_.z);
		float velocityXZ = Math::Length({move_.x, 0.0f, move_.z});
		// X軸周りの角度(θx)
		worldTransform_.rotation_.x = atan2(-move_.y, velocityXZ);
		//  移動
		worldTransform_.translation_ += move_;
	}

	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// ワールドトランスフォームのゲッター
WorldTransform& Player::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// ビュープロジェクションのセッター
void Player::SetViewProjection(const ViewProjection* viewProjection) { directionViewProjection_ = viewProjection; }

// ゲームパッドの操作
void Player::GamePadControl() {
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		isMove_ = true;//移動した
		// 移動量
		move_ = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
	} else {
		move_ = {};
		isMove_ = false;//移動をやめた
	}
}

// キーボードの操作
void Player::KeyBoaeredControl() {
	bool right = Input::GetInstance()->PushKey(DIK_D);
	bool left = Input::GetInstance()->PushKey(DIK_A);
	bool front = Input::GetInstance()->PushKey(DIK_W);
	bool back = Input::GetInstance()->PushKey(DIK_S);
	if (right || left || front || back) {
		isMove_ = true;//移動した
		//左右移動
		if (right) {
			move_.x = 1.0f;
		} else if (left) {
			move_.x = -1.0f;
		} else {
			move_.x = 0.0f;
		}
		//前後移動
		if (front) {
			move_.z = 1.0f;
		} else if (back) {
			move_.z = -1.0f;
		} else {
			move_.z = 0.0f;
		}
	} else {
		isMove_ = false;//移動をやめた
	}
}
