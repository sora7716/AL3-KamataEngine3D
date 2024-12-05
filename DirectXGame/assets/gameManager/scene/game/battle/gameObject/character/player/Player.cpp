#include "Player.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include "assets/math/easing/Easing.h"
#include "input/Input.h"
#include <cassert>

void (Player::*Player::ActionTable[])() = {
    &BehaviorRootUpdate,
    &BehaviorBlowUpdate,
    &BehaviorDashUpdate,
};

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
	if (playerModel_->GetBehavior() != BehaviorMode::kDash) {
		BehaviorRootUpdate();
	} else {
		BehaviorDashUpdate();
	}
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
	if (Input::GetInstance()->GetJoystickState(0, joyState_) && Input::GetInstance()->GetJoystickStatePrevious(0, preJoyState_)) {
		// 移動
		const float deadZone = 0.7f * SHRT_MAX; // デッドソーン
		isMoving_ = false;                      // 移動してない
		// 移動量
		move_ = {(float)joyState_.Gamepad.sThumbLX, 0.0f, (float)joyState_.Gamepad.sThumbLY};
		if (Math::Norm(move_) > deadZone) {
			isMoving_ = true;
		} else {
			isMoving_ = false; // 移動をやめた
		}
		// 攻撃
		if ((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) && !(preJoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
			if ((playerModel_->GetActionTimer() <= 0.0f && playerModel_->GetBehavior() == BehaviorMode::kBlow) || 
				playerModel_->GetBehavior() != BehaviorMode::kBlow) {
				playerModel_->SetBehaviorRequest(BehaviorMode::kBlow);
				playerModel_->SetActionTime((float)kBlowTime);
			}
		}
		if ((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(preJoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			BehaviorDashInitialize();
		} else {
			speed_ = kSpeed_;
		}
	}
}

// キーボードの操作
void Player::KeyboardControl() {
	bool right = Input::GetInstance()->PushKey(DIK_D);
	bool left = Input::GetInstance()->PushKey(DIK_A);
	bool front = Input::GetInstance()->PushKey(DIK_W);
	bool back = Input::GetInstance()->PushKey(DIK_S);
	bool isAttack = Input::GetInstance()->IsTriggerMouse(0);
	bool isDash = Input::GetInstance()->TriggerKey(DIK_LSHIFT);
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
	if (isAttack && playerModel_->GetActionTimer() <= 0.0f) {
		playerModel_->SetBehaviorRequest(BehaviorMode::kBlow);
		playerModel_->SetActionTime((float)kBlowTime);
	}
	if (isDash) {
		BehaviorDashInitialize();
	}
}

// ダッシュの初期化
void Player::BehaviorDashInitialize() {
	isMoving_ = true;
	worldTransform_.rotation_.y = goalAngle_;
	playerModel_->SetBehaviorRequest(BehaviorMode::kDash);
	playerModel_->SetActionTime((float)kBehaviorDashTime);
	isMoving_ = true;
	move_ = {0, 0, 1.0f};
	speed_ = 3.0f / speedScaler_;
}

// ダッシュの更新
void Player::BehaviorDashUpdate() { Moving(speed_ * speedScaler_); }

// 通常行動用
void Player::BehaviorRootUpdate() { Moving(speed_); }

// 打撃用
void Player::BehaviorBlowUpdate() {
	if (!isBlow_) {
		isBlow_ = true;
		blowBeginPos_ = worldTransform_.translation_.z;
	}
	worldTransform_.translation_.z = std::lerp(worldTransform_.translation_.z, blowBeginPos_ + 10.0f, 0.1f);
}

// 移動
void Player::Moving(float speed) {
	// 移動量に速さを反映
	if (isMoving_) {
		move_ = Math::Normalize(move_) * speed;
		Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
		move_ = Math::TransformNormal(move_, rotMat);
		// Y軸周りの角度(θy)
		goalAngle_ = atan2(move_.x, move_.z);
		// 移動
		worldTransform_.translation_ += move_;
	}
	worldTransform_.rotation_.y = Math::LerpShortAngle(worldTransform_.rotation_.y, goalAngle_, rotateFrame_);
}
