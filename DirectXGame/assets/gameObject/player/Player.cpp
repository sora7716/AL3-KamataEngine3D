#include "Player.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/gameobject/lockOn/LockOn.h"
#include "assets/gameobject/hammer/Hammer.h"
#include "assets/failLoad/GlobalVariables.h"

#include "cassert"
#ifdef _DEBUG
#include <imgui.h>
using namespace ImGui;
#endif // _DEBUG

const std::array<Player::ConstAttack, Player::ComboNum> Player::kConstAttacks_ = {
    {// 振りかぶり、攻撃前硬直,攻撃振り時間、硬直、各フェーズの移動速さ
     {0, 0, 45, 0, 0.0f, 0.0f, 0.15f},
     {10, 5, 10, 10, 0.363f, 0.4f, 0.16f},
     {0, 0, 20, 0, 0.0f, 0.0f, 0.15f}}
};

// 初期化処理
void Player::Initialize(std::vector<Model*> models, ViewProjection* viewProjection) {

	BaseCharacter::Initialize(models, viewProjection);
	viewProjection_ = viewProjection;
	input_ = Input::GetInstance();

	InitializeWorldTransform();
	InitializeFloatingGimmick();

	Collider::SetTypeID(static_cast<uint32_t>(CollisionTypeIdDef::kPlayer));

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Player";

	globalVariables->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "body Translate", worldTransforms_[int(typeBody)]->translation_);
	globalVariables->AddItem(groupName, "head Translate", worldTransforms_[int(typeHead)]->translation_);
	globalVariables->AddItem(groupName, "L_Arm Translate", worldTransforms_[int(typeL_arm)]->translation_);
	globalVariables->AddItem(groupName, "R_Arm Translate", worldTransforms_[int(typeR_arm)]->translation_);
	globalVariables->AddItem(groupName, "FloatingCycle", cycle_);
	globalVariables->AddItem(groupName, "FloatingAmplitube", amplitube);
	globalVariables->AddItem(groupName, "idelArmAngleMax", armAngle_);

	
}

// 更新処理
void Player::Update() {

	ApplyGlobalVariables();
	
	InitializeBehavior();
	UpdateBehavior();

#ifdef _DEBUG
	DragFloat3("player.translate", &worldTransforms_[int(typeBase)]->translation_.x, 0.01f);
	DragFloat3("body.translate", &worldTransforms_[int(typeBody)]->translation_.x, 0.01f);
	DragFloat3("kLeftArm.rotation", &worldTransforms_[int(typeL_arm)]->rotation_.x, 0.01f);
	DragInt("parameter", &workAttack_.attackParameter_, 0.01f);
	DragInt("combo", &workAttack_.comboIndex, 0.01f);
	//Checkbox("Hit", &isHit_);
#endif // _DEBUG
}

// 描画処理
void Player::Draw() {
	hammer_->Draw();
	// 3Dモデルを描画
	models_[int(typeBody)]->Draw(*worldTransforms_[int(typeBody)], *viewProjection_); // 体
	models_[int(typeHead)]->Draw(*worldTransforms_[int(typeHead)], *viewProjection_); // 頭
	models_[int(typeL_arm)]->Draw(*worldTransforms_[int(typeL_arm)], *viewProjection_); // 左腕
	models_[int(typeR_arm)]->Draw(*worldTransforms_[int(typeR_arm)], *viewProjection_);  // 右腕
}

// 衝突時処理
void Player::OnCollision([[maybe_unused]] Collider* other) {
	uint32_t typeID = other->GetTypeID();
	// もし衝突相手のIDがkEnemyであるならば
	if (typeID == static_cast<uint32_t>(CollisionTypeIdDef::KEnemy)) {
		// ジャンプ行動をリクエストする
		 behaviorRequest_ = Behavior::kJump;
	}
}

// 中心座標取得
Vector3 Player::GetCenterPosition() const {
	// ローカル座標でのオフセット
	const Vector3 offset = {0.f, 1.5f, 0.f};
	// ワールド座標に変換
	Vector3 worldPos = Transform(offset, worldTransforms_[int(typeBase)]->matWorld_);
	return worldPos;
}

#pragma region 初期化処理メンバ関数の定義

// 各ワールド変換データの初期化
void Player::InitializeWorldTransform() {

	// 各パーツのワールド変換データを初期化する
	for (int i = 0; i < 5; i++) {
		worldTransforms_.resize(5);
		WorldTransform* worldTransform = new WorldTransform();
		worldTransform->Initialize();
		worldTransforms_[i] = worldTransform;
	}

	// 体の親子関係
	worldTransforms_[int(typeBody)]->parent_ = GetWorldTransform()[int(typeBase)];

	// 頭の親子関係
	worldTransforms_[int(typeHead)]->parent_ = GetWorldTransform()[int(typeBody)];
	worldTransforms_[int(typeHead)]->translation_ = {0.0f, 1.504f, 0.0f}; // 座標設定

	// 左腕の親子関係
	worldTransforms_[int(typeL_arm)]->parent_ = GetWorldTransform()[int(typeBody)];
	worldTransforms_[int(typeL_arm)]->translation_ = {-0.527f, 1.262f, 0.0f}; // 座標設定

	// 右腕の親子関係
	worldTransforms_[int(typeR_arm)]->parent_ = GetWorldTransform()[int(typeBody)];
	worldTransforms_[int(typeR_arm)]->translation_ = {0.527f, 1.262f, 0.0f}; // 座標設定

}

// 浮遊ギミック初期化
void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

// 通常行動初期化
void Player::BehaviorRootInitialize() {
	hammer_->ClearContactRecord();
	hammer_->SetScale(Vector3());
}

// 攻撃行動初期化
void Player::BehaviorAttackInitialize() {
	worldTransforms_[int(typeBody)]->translation_.y = 0;
	worldTransforms_[int(typeL_arm)]->rotation_.x = -1.53f;
	worldTransforms_[int(typeR_arm)]->rotation_.x = -1.53f;
	hammer_->SetScale(Vector3(1, 1, 1));
	hammer_->SetRotation({.x = 3.0f});

	// 攻撃の初期化でボディと親子関係を結ぶ
	if (hammer_) {
		hammer_->SetParent(this->GetWorldTransform()[int(typeBody)]);
	}

	// ハンマーの接触履歴を抹消する
	hammer_->ClearContactRecord();

	workAttack_.attackParameter_ = 0;
	attackPhase_ = AttackPhase::kAticipation;

}

// ダッシュ行動初期化
void Player::BehaviorDashInitialize() {
	workDash_.dashParameter_ = 0;
	worldTransforms_[int(typeBase)]->rotation_.y = destinationAngleY;
	worldTransforms_[int(typeL_arm)]->rotation_.x = 0.5f;
	worldTransforms_[int(typeR_arm)]->rotation_.x = 0.5f;
}

// ジャンプ行動初期化
void Player::BehaviorJumpInitialize() {

	worldTransforms_[int(typeBody)]->translation_.y = 0;
	worldTransforms_[int(typeL_arm)]->rotation_.x = 0;
	worldTransforms_[int(typeR_arm)]->rotation_.x = 0;

	// ジャンプ初速
	const float kJumpFirstSpeed = 1.0f;
	// ジャンプ初速を与える
	velocity_.y = kJumpFirstSpeed;
}

// ふるまいの初期化
void Player::InitializeBehavior() {

	if (behaviorRequest_) {
		// ふるまいを変更する
		behavior_ = behaviorRequest_.value();

		// ふるまい初期化をメンバ関数ポインタで呼び出す
		(this->*behaviorInitializeTable[static_cast<size_t>(behavior_)])();

		behaviorRequest_ = std::nullopt;
	}
}

#pragma endregion

#pragma region 移動処理

// ゲームパッド操作
bool Player::GamePadController() {
	XINPUT_STATE joyState;

	if (input_->GetJoystickState(0, joyState)) {
		const float deadZone = 0.7f;

		velocity_ = {(float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.f, (float)joyState.Gamepad.sThumbLY / SHRT_MAX};

		if (Math::Length(velocity_) > deadZone) {
			return true;
		}
	}

	return false;
}

// ジョイスティックによる移動
void Player::JoyStickMove(const float speed) {

	if (this->GamePadController()) {
		isMoving = true;
	} else {
		isMoving = false;
	}

	if (isMoving) {

		velocity_ = Math::Normalize(velocity_) * speed;

		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);

		velocity_ = TransformNormal(velocity_, rotateYMatrix);

		worldTransforms_[int(typeBase)]->translation_ += velocity_;

		targetRotate_.y = std::atan2(velocity_.x, velocity_.z);
	} else if (lockOn_ && lockOn_->ExistTarget()) {
		// ロックオン対象の座標取得
		Vector3 lockOnPos = lockOn_->GetTargetPosition();
		// 追従対象からロックオン対象へのベクトルを求める
		Vector3 sub = lockOnPos - this->GetCenterPosition();
		// Y軸周り角度
		worldTransforms_[int(typeBase)]->rotation_.y = std::atan2(sub.x, sub.z);
	}

	worldTransforms_[int(typeBase)]->rotation_.y = 
		LerpShortAngle(worldTransforms_[int(typeBase)]->rotation_.y, targetRotate_.y, destinationAngleY);
}

#pragma endregion 

#pragma region 浮遊

void Player::UpdateFloatingGimmick() {

	///===================================================<浮遊アニメーション>========================================================

	// 1フレーム出のパラメータ加算値
	const float step = 2.0f * pi_f / cycle_;
	// パラメータを1ステップ分加算
	floatingParameter_ += step;
	// 2π超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * pi_f);
	// 浮遊を座標に反映
	this->PartAnimation(std::sin(floatingParameter_));
};

void Player::PartAnimation(float parameter) {
	int32_t index = 1;

	// for文をパーツ数以下であれば処理を繰り返す
	for (index = 1; index < int(PartsNum); index++) {
		
		// インデックスが1なら
		if (index == 1) {
		
			// ワールド変換データのトランスフォームYを動かす
			worldTransforms_[index]->translation_.y = parameter * amplitube;
		
			// インデックスが3かつ4なら
		} else if (index == 3 || index == 4) {

			// ワールド変換データのX軸周りを回転させる
			worldTransforms_[index]->rotation_.x = parameter * armAngle_;
		
		}
	}
}

#pragma endregion 

#pragma region ふるまい更新

// 通常行動
void Player::BehaviorRootUpdate() {

	XINPUT_STATE joyState;

	const float speed = 0.3f;

	JoyStickMove(speed);
	UpdateFloatingGimmick();

	if (!input_->GetJoystickState(0, joyState)) {
		return;
	}

	// 攻撃ボタンを押したら
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		// 攻撃リクエスト
		behaviorRequest_ = Behavior::kAttack;
	}

	// ダッシュボタンを押したら
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		// ダッシュリクエスト
		behaviorRequest_ = Behavior::kDash;
	}

	// ジャンプボタンを押したら
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		// ジャンプリクエスト
		behaviorRequest_ = Behavior::kJump;
	}
}

// 攻撃行動
void Player::BehaviorAttackUpdate() {

	// ロックオン状態なら
	if (lockOn_ && lockOn_->ExistTarget()) {
		// ロックオン対象の座標取得
		Vector3 lockOnPos = lockOn_->GetTargetPosition();
		// 追従対象からロックオン対象へのベクトルを求める
		Vector3 sub = lockOnPos - this->GetCenterPosition();
		// 距離
		float distance = Math::Length(sub);
		// 距離しきい値
		const float threshold = 0.2f;
		// しきい値より離れている時のみ
		if (distance > threshold) {
			// Y軸周り角度
			worldTransforms_[int(typeBase)]->rotation_.y = std::atan2(sub.x, sub.z);

			// しきい値を超える速さなら補正する
			if (speed_ > distance - threshold) {
				// ロックオン対象へのめり込み防止
				speed_ = distance - threshold;
			}
		}
	}

	workAttack_.attackParameter_++;
	
	(this->*attackTable[static_cast<size_t>(attackPhase_)])();

	int32_t totalAttackTime = kConstAttacks_[1].anticipationTime + kConstAttacks_[1].chargeTime + kConstAttacks_[1].swingTime + kConstAttacks_[1].recoveryTime;

	if (workAttack_.attackParameter_ >= totalAttackTime) {
		worldTransforms_[int(typeBody)]->rotation_.y = 0.0f;
		workAttack_.attackParameter_ = 0;
		workAttack_.comboIndex = 0;
		behaviorRequest_ = Behavior::kRoot;
	}
};

// ダッシュ行動
void Player::BehaviorDashUpdate() {

	const float dashSpeed = 0.7f;
	JoyStickMove(dashSpeed);

	// ダッシュの時間<frame>
	const int32_t behaviorDashTime = 60;
	// 既定の時間経過で通常行動に戻る
	if (++workDash_.dashParameter_ >= behaviorDashTime) {
		behaviorRequest_ = Behavior::kRoot;
	}
}

// ジャンプ行動
void Player::BehaviorJumpUpdate() {

	// 移動
	worldTransforms_[int(typeBase)]->translation_ += velocity_;
	// 重力加速度
	const float kGravityAcceleration = 0.075f;
	// 加速度ベクトル
	Vector3 accelerationVector = {0, -kGravityAcceleration, 0};
	// 加速する
	velocity_ += accelerationVector;
	// 着地
	if (worldTransforms_[int(typeBase)]->translation_.y <= 0.0f) {
		worldTransforms_[int(typeBase)]->translation_.y = 0;
		// ジャンプ終了
		behaviorRequest_ = Behavior::kRoot;
	}
}

// ふるまい更新
void Player::UpdateBehavior() {

	// ふるまい更新をメンバ関数ポインタで呼び出す
	(this->*behaviorUpdateTable[static_cast<size_t>(behavior_)])();
	hammer_->Update();
	// 行列を更新する
	for (auto worldTransform : worldTransforms_) {
		worldTransform->UpdateMatrix();
	}
}

#pragma endregion 

#pragma region 行動が攻撃時の更新処理

void Player::UpdateAticipation() {

	if (workAttack_.attackParameter_ > 0 && workAttack_.attackParameter_ < 10) {
		worldTransforms_[int(typeL_arm)]->rotation_.x += kConstAttacks_[1].anticipationSpeed * 1.45f;
		worldTransforms_[int(typeR_arm)]->rotation_.x += kConstAttacks_[1].anticipationSpeed * 1.45f;
		Vector3 hammerAngle = hammer_->GetRotation(); // ハンマーの回転
		hammerAngle.x += kConstAttacks_[1].anticipationSpeed;
		hammer_->SetRotation(hammerAngle);
	}

	if (workAttack_.attackParameter_ >= 10) {
		attackPhase_ = AttackPhase::kCharge;
	}
}

void Player::UpdateCharge() {
	if (workAttack_.attackParameter_ > 11 && workAttack_.attackParameter_ < 16) {

		Vector3 forward = Math::TransformNormal({0, 0, 1}, worldTransforms_[int(typeBase)]->matWorld_);
		worldTransforms_[int(typeBase)]->translation_ += forward * kConstAttacks_[1].chargeSpeed;
	}

	if (workAttack_.attackParameter_ >= 16) {
		attackPhase_ = AttackPhase::kSwing;
	}
}

void Player::UpdateSwing() {
	if (workAttack_.attackParameter_ > 17 && workAttack_.attackParameter_ < 28) {
		worldTransforms_[int(typeL_arm)]->rotation_.x += kConstAttacks_[1].swingSpeed;
		worldTransforms_[int(typeR_arm)]->rotation_.x += kConstAttacks_[1].swingSpeed;
		Vector3 hammerAngle = hammer_->GetRotation();
		hammerAngle.x += kConstAttacks_[1].swingSpeed;
		hammer_->SetRotation(hammerAngle);
	}
}

#pragma endregion

// デバッグテキストの描画
void Player::DrawDebugText() {

#ifdef _DEBUG
	SliderFloat3("Body Translate", &worldTransforms_[int(typeBody)]->translation_.x, -5.0f, 5.0f);
	SliderFloat3("Head Translate", &worldTransforms_[int(typeHead)]->translation_.x, -5.0f, 5.0f);
	SliderFloat3("L_arm Rotation", &worldTransforms_[int(typeL_arm)]->rotation_.x, -5.0f, 5.0f);
	SliderFloat3("R_arm Rotation", &worldTransforms_[int(typeR_arm)]->rotation_.x, -5.0f, 5.0f);
	SliderInt("FloatingCycle", &cycle_, 1, 200);
	SliderFloat("FloaingAmplitube", &amplitube, 0, 10);
	SliderFloat("IdelArmAngleMax", &armAngle_, 0, 3.5f);
#endif // _DEBUG
}

void Player::ApplyGlobalVariables() {

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Player";

	worldTransforms_[int(typeBody)]->translation_ = globalVariables->GetVector3Value(groupName, "body Translate");
	worldTransforms_[int(typeHead)]->translation_ = globalVariables->GetVector3Value(groupName, "head Translate");
	worldTransforms_[int(typeL_arm)]->translation_ = globalVariables->GetVector3Value(groupName, "L_Arm Translate");
	worldTransforms_[int(typeR_arm)]->translation_ = globalVariables->GetVector3Value(groupName, "R_Arm Translate");
	cycle_ = globalVariables->GetIntValue(groupName, "FloatingCycle");
	amplitube = globalVariables->GetFloatValue(groupName, "FloatingAmplitube");
	armAngle_ = globalVariables->GetFloatValue(groupName, "idelArmAngleMax");
}

#pragma region 各メンバ関数ポインタの宣言

// ふるまいの初期化
void (Player::*Player::behaviorInitializeTable[])(){
	&Player::BehaviorRootInitialize, 
	&Player::BehaviorAttackInitialize, 
	&Player::BehaviorDashInitialize, 
	&Player::BehaviorJumpInitialize
};
// 攻撃フェーズ
void (Player::*Player::attackTable[])(){
    &Player::UpdateAticipation,
    &Player::UpdateCharge,
    &Player::UpdateSwing,
};
// ふるまいの更新
void (Player::*Player::behaviorUpdateTable[])(){
	&Player::BehaviorRootUpdate, 
	&Player::BehaviorAttackUpdate, 
	&Player::BehaviorDashUpdate, 
	&Player::BehaviorJumpUpdate
};

#pragma endregion 