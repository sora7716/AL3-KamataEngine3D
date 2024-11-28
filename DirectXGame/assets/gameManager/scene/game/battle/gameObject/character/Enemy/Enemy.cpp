#include "Enemy.h"

#pragma region ミミック
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
	circulaMoveRadius_ = {0.5f, 0.3f};
}

// 更新
void Mimic::Update() {
	//Move();
	BaseCharacter::Update();
	mimicModel_->Update();
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat2("circularMove.radius", &circulaMoveRadius_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

// 描画
void Mimic::Draw() { 
	mimicModel_->Draw(); 
}

//移動
void Mimic::Move() {
	// 円運動
	velocity_ = Math::CircularMoveVeclocityXZ(circulaMoveRadius_, kSpeed);
	// Y軸周りの角度(θy)
	worldTransform_.rotation_.y = atan2(velocity_.x, velocity_.z);
	float velocityXZ = Math::Length({velocity_.x, 0.0f, velocity_.z});
	// X軸周りの角度(θx)
	worldTransform_.rotation_.x = atan2(-velocity_.y, velocityXZ);
	worldTransform_.translation_ += velocity_;
}
#pragma endregion
