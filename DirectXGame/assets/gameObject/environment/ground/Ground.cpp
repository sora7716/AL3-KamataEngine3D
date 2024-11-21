#include "Ground.h"

// 初期化
void Ground::Initialize(ViewProjection* viewProjection, Model* model) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

// 更新
void Ground::Update() { worldTransform_.UpdateMatrix(); }

// 描画
void Ground::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
