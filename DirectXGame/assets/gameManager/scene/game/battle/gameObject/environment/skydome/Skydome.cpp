#include "Skydome.h"

// 初期化
void Skydome::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

// 更新
void Skydome::Update() { worldTransform_.UpdateMatrix(); }

// 描画
void Skydome::Draw() {
	if (model_) {
		model_->Draw(worldTransform_, *viewProjection_);
	}
}
