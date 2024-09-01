#include "Ground.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <numbers>

// 初期化
void Ground::Initialise(Model* model, ViewProjection* viewProjection) { 
	assert(model);
	model_ = model;//モデルを受け取る
	viewProjection_ = viewProjection;//ビュープロジェクションを受け取る
	worldTransform_.Initialize();
	worldTransform_.translation_.y = -300.0f;
	worldTransform_.rotation_.x = -std::numbers::pi_v<float> / 2.0f;
}

// 更新
void Ground::Update() { worldTransform_.UpdateMatrix(); }

// 描画
void Ground::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
