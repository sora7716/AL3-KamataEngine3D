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

// デストラクタ
Player::~Player() {
	delete horizontalCommand_;
	delete verticalCommand_;
}

// 初期化
void Player::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection, const std::vector<uint32_t>&& textures) {
	BaseCharacter::Initialize(std::move(models), viewProjection, std::move(textures));
	worldTransform_.translation_.y = -2.9f;
	// プレイヤーモデルの生成
	playerModel_ = std::make_unique<PlayerModel>();
	// プレイヤーモデルの初期化
	playerModel_->Initialize(std::move(models_), viewProjection_);
	// プレイヤーとの親子付け
	playerModel_->SetParent(&worldTransform_);
	//コライダーの設定
	colliderScale_ = {1.0f, 1.4f, 0.6f};
	colliderPos_ = {0.0f, 1.3f, -0.1f};
	// 入力キーの生成
	CreateInputKey();

	charType_ = CharType::kPlayer;
	// 体力
	playerLifeBar_ = std::make_unique<LifeBar>(GetCharacterType());
	playerLifeBar_->Initialize(std::move(textures));

	playerMpBar_ = std::make_unique<MpBar>(GetCharacterType());
	playerMpBar_->Initialize(std::move(textures));
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
	wireFrame_->SetScale(colliderScale_);
	wireFrame_->SetRotate(worldTransform_.rotation_);
	wireFrame_->SetPosition(
		Vector3(worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2])+colliderPos_);
#ifdef _DEBUG
	ImGui::Begin("playerCollder");
	ImGui::DragFloat3("scale", &colliderScale_.x, 0.1f, 0.0f, 5.0f);
	ImGui::DragFloat3("translate", &colliderPos_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	isDead_ = playerLifeBar_->Update();

	BaseCharacter::Update(); // 更新
}

// 描画
void Player::Draw() {
	// プレイヤーモデルの描画
	playerModel_->Draw();
}

void Player::DrawSprite(){
	playerLifeBar_->Draw();
	playerMpBar_->Draw();
}

// ビュープロジェクションのセッター
void Player::SetViewProjection(const ViewProjection* viewProjection) { directionViewProjection_ = viewProjection; }

// ダッシュの初期化
void Player::BehaviorDashInitialize() {
	isMoving_ = true;
	worldTransform_.rotation_.y = goalAngle_;
	playerModel_->SetBehaviorRequest(BehaviorMode::kDash);
	playerModel_->SetActionTime((float)kBehaviorDashTime);
	isMoving_ = true;
	move_ = {0, 0, 1.0f};
	speed_ = 3.0f;
}

// ダッシュの更新
void Player::BehaviorDashUpdate() { Moving(speed_ * speedScaler_); }

//ワイヤーフレームのゲッター
OBB* Player::GetWireFrame() { return wireFrame_; }

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
		// move_ = Math::TransformNormal(move_, rotMat);
		//   Y軸周りの角度(θy)
		goalAngle_ = atan2(move_.x, move_.z);
		// 移動
		worldTransform_.translation_ += move_;
	}
	worldTransform_.rotation_.y = Math::LerpShortAngle(worldTransform_.rotation_.y, goalAngle_, rotateFrame_);
}

// ゲームパッドの操作
void Player::GamepadControl() {
	if (Input::GetInstance()->GetJoystickState(0, joyState_) && Input::GetInstance()->GetJoystickStatePrevious(0, preJoyState_)) {
		// 移動
		const float deadZone = 0.7f * SHRT_MAX; // デッドソーン
		isMoving_ = false;                      // 移動してない
		// 移動量
		move_ = {(float)joyState_.Gamepad.sThumbLX, 0.0f, (float)joyState_.Gamepad.sThumbLY};
		if (Math::Norm(move_) > deadZone && !(playerModel_->GetBehavior() == BehaviorMode::kBlow)) {
			isMoving_ = true;
		} else {
			isMoving_ = false; // 移動をやめた
		}
		// 攻撃
		if ((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) && !(preJoyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
			if ((playerModel_->GetActionTimer() <= 0.0f && playerModel_->GetBehavior() == BehaviorMode::kBlow) || playerModel_->GetBehavior() != BehaviorMode::kBlow) {
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

#pragma region キーボード
// キーボードの操作
void Player::KeyboardControl() {
	bool attack = Input::GetInstance()->IsTriggerMouse(0) && playerModel_->GetActionTimer() <= 0.0f;
	//	bool isBlowNow = playerModel_->GetBehavior() == BehaviorMode::kBlow;
	bool dash = Input::GetInstance()->TriggerKey(DIK_LSHIFT);
	// 水平移動
	horizontalCommand_ = inputHandle_->HorizontalMoveCommand();
	if (horizontalCommand_) {
		horizontalCommand_->Exec(this);
	}
	// 垂直移動
	verticalCommand_ = inputHandle_->VerticalMoveCommand();
	if (verticalCommand_) {
		verticalCommand_->Exec(this);
	}
	// 移動フラグ
	isMoving_ = isHorizontalMove_ || isVerticalMove_;

	if (attack) {
		playerModel_->SetBehaviorRequest(BehaviorMode::kBlow);
		playerModel_->SetActionTime((float)kBlowTime);
	}
	if (dash) {
		BehaviorDashInitialize();
	}
}

// 左に進む
void Player::MoveLeftKeyboard() {
	isHorizontalMove_ = true;
	move_.x = -1.0f;
}

// 右に進む
void Player::MoveRightKeyboard() {
	isHorizontalMove_ = true;
	move_.x = 1.0f;
}

// 横移動を止める
void Player::StopHorizontal() {
	isHorizontalMove_ = false;
	move_.x = 0.0f;
}

// 前に進む
void Player::MoveFrontKeyboard() {
	isVerticalMove_ = true;
	move_.z = 1.0f;
}

// 後ろに進む
void Player::MoveBackKeyboard() {
	isVerticalMove_ = true;
	move_.z = -1.0f;
}

// 垂直移動を止める
void Player::StopVertical() {
	isVerticalMove_ = false;
	move_.z = 0.0f;
}

// キーの生成
void Player::CreateInputKey() {
	inputHandle_ = std::make_unique<InputHandle>();
	for (int i = 0; i < 6; i++) {
		(inputHandle_.get()->*InputHandle::AssignCommandTable[i])();
	}
}
#pragma endregion
