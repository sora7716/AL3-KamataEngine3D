#include "Enemy.h"

#pragma region ミミック
//初期化
void Mimic::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection){ 
	BaseCharacter::Initialize(std::move(models),viewProjection);
	//モデルの生成
	mimicModel_ = std::make_unique<MimicModel>();
	//モデルの初期化
	mimicModel_->Initialize(std::move(models_), viewProjection_);
	//モデルの親子付け
	mimicModel_->SetParent(&worldTransform_);
}

//更新
void Mimic::Update() { 
	//円運動
	Math::CircularMoveXZ(circulaMoveCenter_, velocity_,circulaMoveRadius_);
	// Y軸周りの角度(θy)
	worldTransform_.rotation_.y = atan2(velocity_.x, velocity_.z);
	float velocityXZ = Math::Length({velocity_.x, 0.0f, velocity_.z});
	//X軸周りの角度(θx)
	worldTransform_.rotation_.x = atan2(-velocity_.y, velocityXZ);

	worldTransform_.translation_ = velocity_;

	BaseCharacter::Update();
	mimicModel_->Update();
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("circularMove.center", &circulaMoveCenter_.x, 0.1f);
	ImGui::DragFloat2("circularMove.radius", &circulaMoveRadius_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

//描画
void Mimic::Draw() { mimicModel_->Draw(); }
#pragma endregion
