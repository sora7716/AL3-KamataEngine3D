#include "BaseEnvironment.h"

//初期化
void BaseEnvironment::Initialize(ViewProjection* viewProjection, std::shared_ptr<Model>&& model) { 
	assert(model.get());
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

//更新
void BaseEnvironment::Update() { worldTransform_.UpdateMatrix(); }

//描画
void BaseEnvironment::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
