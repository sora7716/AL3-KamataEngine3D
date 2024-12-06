#include "Enemy.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"

#pragma region ミミック
// メンバ関数ポインタの配列の初期化
void (Mimic::*Mimic::ActionModeTable[])(){
    &Idle,
    &Move,
    &MoveToward,
    &Attack,
	&CoolDown
};

void(Mimic::* Mimic::AnimationTable[])() {
	&BehaviorRootUpdate,
	&BehaviorBiteUpdate,
};

// 初期化
void Mimic::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	BaseCharacter::Initialize(std::move(models), viewProjection);
	// モデルの生成
	mimicModel_ = std::make_unique<MimicModel>();
	// モデルの初期化
	mimicModel_->Initialize(std::move(models_), viewProjection_);
	// モデルの親子付け
	mimicModel_->SetParent(&worldTransform_);
	worldTransform_.translation_ = {.x = 30.0f, .y = 0.0f, .z = 40.0f};
	worldTransform_.rotation_.x = 0.3f;
	circulaMoveRadius_ = {0.5f, 0.3f};

	charType_ = CharType::kEnemy;
}

// 更新
void Mimic::Update() {
	// ステータスの変更
	ChangeStatus();
	// 行動
	(this->*Mimic::ActionModeTable[status_])();
	(this->*Mimic::AnimationTable[(int)mimicModel_->GetBehavior()])();
	BaseCharacter::Update();
	mimicModel_->Update();
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat2("circularMove.radius", &circulaMoveRadius_.x, 0.1f);
	ImGui::Text("waitTime:%f", waitTime_);
	ImGui::Text("coolTime:%f", coolTime_);
	ImGui::End();
#endif // _DEBUG
}

// 描画
void Mimic::Draw() { mimicModel_->Draw(); }

// 攻撃
void Mimic::Attack() {
	isAttacking = true;
	mimicModel_->SetBehavior(BehaviorMode::kBite);
}

// プレイヤーのセッター
void Mimic::SetPlayer(Player* player) { player_ = player; }

// ターゲットに向かって移動
void Mimic::MoveToward() {
	// Targetはおそらくプレイヤーとなって距離を計算して
	Vector3 dist = {player_->GetPosition().x - worldTransform_.translation_.x,
		player_->GetPosition().y - worldTransform_.translation_.y,
		player_->GetPosition().z - worldTransform_.translation_.z};

	float magnitude = std::sqrtf(powf(dist.x, 2) + powf(dist.y, 2) + powf(dist.z, 2));

	// velocityを求める
	velocity_ = {(dist.x / magnitude) * kSpeed, (dist.y / magnitude) * kSpeed, (dist.z / magnitude) * kSpeed};
	// lerpで位置を更新する処理
	Vector3 endDestination = worldTransform_.translation_ + velocity_;
	worldTransform_.translation_ = Math::Lerp(worldTransform_.translation_, endDestination, 0.2f);
	Direction();
}

// 移動
void Mimic::Move() {
	isAttacking = false;
	// 円運動
	velocity_ = Math::CircularMoveVeclocityXZ(circulaMoveRadius_, kSpeed);
	// Y軸周りの角度(θy)
	worldTransform_.rotation_.y = atan2(velocity_.x, velocity_.z);
	float velocityXZ = Math::Length({velocity_.x, 0.0f, velocity_.z});
	//  X軸周りの角度(θx)
	worldTransform_.rotation_.x = atan2(-velocity_.y, velocityXZ);
	worldTransform_.translation_ += velocity_;
	Direction();
}

// 待機
void Mimic::Idle() {
	// 最初のアングルを設定
	if (!isSetStartAngle_) {
		angleTimer_ = 0.0f;
		startAngle_ = degree(worldTransform_.rotation_.y);
		isSetStartAngle_ = true;
	}
	// 回転する
	worldTransform_.rotation_.y = Math::AngleLerp(startAngle_ - 60.0f, startAngle_ + 60.0f, EasingMode::kInSine, 2.0f, angleTimer_);
}

// ミミックのステータスを変更
void Mimic::ChangeStatus() {
	// 敵とプレイヤーの距離
	float distance = Math::Norm(player_->GetPosition() - worldTransform_.translation_);

	if (distance <= kAttackRange) {
		status_ = (int)Status::kAttack;
		coolTime_ = kCoolDownInterval;
	} else if (distance <= kChaseRange) {
		if (coolTime_-- > 0) {
			status_ = (int)Status::kCoolDown;
			return;
		}
		else {
			status_ = (int)Status::kMoveToward;
			// 待機時間を設定
			waitTime_ = kWaitInterval;
		}
	} else {
		if (waitTime_-- > 0) {
			// 待機
			status_ = (int)Status::kIdle;
			return;
		}
		// 最初のアングルを設定をfalse
		isSetStartAngle_ = false;
		// 移動
		status_ = (int)Status::kMove;
	}
}

// 向き
void Mimic::Direction() {
	// Y軸周りの角度(θy)
	worldTransform_.rotation_.y = atan2(velocity_.x, velocity_.z);
}

void Mimic::CoolDown(){
	//isAttacking = false;
	Direction();
}

void Mimic::BehaviorRootReset(){

}

void Mimic::BehaviorRootUpdate(){
	worldTransform_.rotation_.z= Math::AngleLerp(10, -10, EasingMode::kNormal, 1.0f, frame_);
}

void Mimic::BehaviorBiteReset(){

}

void Mimic::BehaviorBiteUpdate(){

}

#pragma endregion