#include "Player.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include "input/Input.h"
#include "assets/math/easing/Easing.h"
#include <cassert>

// 初期化
void Player::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	BaseCharacter::Initialize(std::move(models), viewProjection);
	// プレイヤーモデルの生成
	playerModel_ = std::make_unique<PlayerModel>();
	// プレイヤーモデルの初期化
	playerModel_->Initialize(std::move(models_), viewProjection_);
	// プレイヤーとの親子付け
	playerModel_->SetParent(&worldTransform_);
}

// 更新
void Player::Update() {
	// プレイヤーモデルの更新
	playerModel_->Update();
	BehaviorBlowUpdate();
	BaseCharacter::Update(); // 更新
}

// 描画
void Player::Draw() {
	// プレイヤーモデルの描画
	playerModel_->Draw();
}

// ビュープロジェクションのセッター
void Player::SetViewProjection(const ViewProjection* viewProjection) { directionViewProjection_ = viewProjection; }

// ゲームパッドの操作
void Player::GamepadControl() {
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		const float deadZone = 0.7f * SHRT_MAX; // デッドソーン
		isMoving_ = false;                      // 移動してない
		// 移動量
		move_ = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
		if (Math::Length(move_) > deadZone) {
			isMoving_ = true;
		} else {
			isMoving_ = false; // 移動をやめた
		}
	}
}

// キーボードの操作
void Player::KeyboardControl() {
	bool right = Input::GetInstance()->PushKey(DIK_D);
	bool left = Input::GetInstance()->PushKey(DIK_A);
	bool front = Input::GetInstance()->PushKey(DIK_W);
	bool back = Input::GetInstance()->PushKey(DIK_S);
	if (right || left || front || back) {
		isMoving_ = true; // 移動した
		// 左右移動
		if (right) {
			move_.x = 1.0f;
		} else if (left) {
			move_.x = -1.0f;
		} else {
			move_.x = 0.0f;
		}
		// 前後移動
		if (front) {
			move_.z = 1.0f;
		} else if (back) {
			move_.z = -1.0f;
		} else {
			move_.z = 0.0f;
		}
	} else {
		isMoving_ = false; // 移動をやめた
	}
}

// 通常行動用
void Player::BehaviorRootUpdate() {
	// 移動量に速さを反映
	if (isMoving_) {
		move_ = Math::Normalize(move_) * speed_;
		Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
		move_ = Math::TransformNormal(move_, rotMat);
		// Y軸周りの角度(θy)
		goalAngle_ = atan2(move_.x, move_.z);
		// 移動
		worldTransform_.translation_ += move_;
	}
	worldTransform_.rotation_.y = Math::LerpShortAngle(worldTransform_.rotation_.y, goalAngle_, rotateFrame_);
}

// 打撃用
void Player::BehaviorBlowUpdate() {
	if (!isBlow_) {
		isBlow_ = true;
		blowBeginPos_ = worldTransform_.translation_.z;
	}
	worldTransform_.translation_.z = std::lerp(worldTransform_.translation_.z, blowBeginPos_ + 10.0f, 0.1f);
	if (worldTransform_.translation_.z >= blowBeginPos_ + 10.0f - 0.1f) {
		isBlow_ = false;
	}
}
