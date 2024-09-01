#include "Ground.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void Ground::Initialise(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;                   // モデルを受け取る
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	for (int i = 0; i < 2; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_.y = -300.0f;
		worldTransform_[i].translation_.z = 1000.0f;
		worldTransform_[i].rotation_.x = -std::numbers::pi_v<float> / 2.0f;
	}
}

// 更新
void Ground::Update() {

	if (worldTransform_[0].translation_.z <= -100) {
		worldTransform_[1].translation_.z--;
		worldTransform_[0].translation_.z = 1000.0f;
	} else {
		worldTransform_[0].translation_.z--;
		worldTransform_[1].translation_.z = 1000.0f;
	}
	for (int i = 0; i < 2; i++) {
		worldTransform_[i].UpdateMatrix();
	}
}

// 描画
void Ground::Draw() {
	for (int i = 0; i < 2; i++) {
		model_->Draw(worldTransform_[i], *viewProjection_);
	}
}
