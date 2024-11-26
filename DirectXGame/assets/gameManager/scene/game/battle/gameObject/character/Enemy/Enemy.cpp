#include "Enemy.h"

//初期化
void Enemy::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection){ 
	BaseCharacter::Initialize(std::move(models),viewProjection);
	//モデルの生成
	mimicModel_ = new MimicModel();
	//モデルの初期化
	mimicModel_->Initialize(std::move(models_), viewProjection_);
	//モデルの親子付け
	mimicModel_->SetParent(&worldTransform_);
}

//更新
void Enemy::Update() { 
	BaseCharacter::Update();
	mimicModel_->Update();
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

//描画
void Enemy::Draw() { mimicModel_->Draw(); }
