#include "Ground.h"

// 初期化
void Ground::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

// 更新
void Ground::Update() { worldTransform_.UpdateMatrix(); }

// 描画
void Ground::Draw() {
	if (model_) {
		model_->Draw(worldTransform_, *viewProjection_);
	}
}
