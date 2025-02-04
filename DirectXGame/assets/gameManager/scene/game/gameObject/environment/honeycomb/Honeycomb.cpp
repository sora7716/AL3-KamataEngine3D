#include "Honeycomb.h"

// 初期化
void Honeycomb::Initialize(ViewProjection* viewProjection, std::shared_ptr<Model> model) {
	// ベースの初期化
	BaseEnvironment::Initialize(viewProjection, model);
	worldTransforms_.resize(kHorizontal);
	// 六角形の初期化
	for (int i = 0; i < kHorizontal; i++) {
		worldTransforms_[i].resize(kVertical);
		for (int j = 0; j < kVertical; j++) {
			WorldTransform* worldTransform = new WorldTransform();
			worldTransform->Initialize();
			worldTransform->scale_ = hexagonScale_;
			worldTransform->translation_.x = (j + 0.5f * (i % 2)) * hexagonScale_.x * sqrt(3.0f); // x座標の計算
			worldTransform->translation_.z = i * (1.5f * hexagonScale_.z);                        // z座標の計算
		    // worldTransform->parent_ = &worldTransform_;
			worldTransforms_[i][j] = worldTransform;
		}
	}
}

// 更新
void Honeycomb::Update() {
	// ベースの更新
	BaseEnvironment::Update();
	for (auto& cell : worldTransforms_) {
		for (auto& piece : cell) {
			piece->UpdateMatrix();
		}
	}
}

// 描画
void Honeycomb::Draw() {
	for (auto& cell : worldTransforms_) {
		for (auto& piece : cell) {
			model_->Draw(*piece, *viewProjection_);
		}
	}
}