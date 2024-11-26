#include "Enemy.h"

//初期化
void Enemy::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection){ 
	BaseCharacter::Initialize(std::move(models),viewProjection);
	mimicModel_ = new MimicModel();
	mimicModel_->Initialize(std::move(models_), viewProjection_);
}

//更新
void Enemy::Update() { 
	BaseCharacter::Update();
	mimicModel_->Update();
}

//描画
void Enemy::Draw() { mimicModel_->Draw(); }
