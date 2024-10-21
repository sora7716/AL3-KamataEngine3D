#include "Hexagon.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Aithmetic.h"
#include <cassert>
#ifdef _DEBUG
#include "ImGuiManager.h"
#endif // _DEBUG

// 初期化
void Hexagon::Initialize(Model* model, ViewProjection* viewProjection) {
	model_ = std::move(model);              // モデルを受け取る
	viewProjection_ = viewProjection;       // ビュープロジェクションを受け取る
	polar_.radius = 1.0f;                   // 半径
	polar_.diameter = polar_.radius * 2.0f; // 直径
	worldTransforms_.resize(row);           // 層の数を設定
	parent_ = new WorldTransform();         // 六角形の親の生成
	parent_->Initialize();                  // 六角形の親の初期化
	for (int i = 0; i < row; i++) {
		worldTransforms_[i].resize(col);
		for (int j = 0; j < col; j++) {
			WorldTransform* worldTransform = new WorldTransform();
			worldTransform->Initialize();
			worldTransform->translation_.x = polar_.diameter * j + (polar_.radius * i);
			worldTransform->translation_.y = polar_.diameter * i - ((polar_.radius / 2.0f) * i);
			worldTransform->translation_.z = 20.0f;
			worldTransform->rotation_.x = pi_f / 2.0f;
			worldTransform->parent_ = parent_;
			worldTransforms_[i][j] = worldTransform;
		}
	}
}

// 更新
void Hexagon::Update() {
	ImGui::Begin("Hexagon");
	ImGui::DragFloat3("rotation", &parent_->rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &parent_->translation_.x, 0.1f);
	ImGui::End();
	for (auto piece : worldTransforms_) {
		for (auto& worldTransform : piece) {
			if (worldTransform) {
				worldTransform->UpdateMatrix(); // 行列の更新
			}
		}
	}
	parent_->UpdateMatrix(); // 親の行列の更新
}

// 描画
void Hexagon::Draw() {
	for (auto piece : worldTransforms_) {
		for (auto& worldTransform : piece) {
			if (worldTransform) {
				model_->Draw(*worldTransform, *viewProjection_);
			}
		}
	}
}
