#include "Luminous.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include "cassert"
#include "input/Input.h"
// 初期化
void Luminous::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransforms_.resize(7);
	for (int i = 0; i < worldTransforms_.size(); i++) {
		WorldTransform* worldTranform = new WorldTransform;
		worldTranform->Initialize();
		worldTranform->translation_.y = 3.0f;
		worldTransforms_[i] = worldTranform;
	}
	for (int i = 1; i < worldTransforms_.size(); i++) {
		worldTransforms_[i]->scale_ = {kSize, kSize, kSize};
	}
}

// 更新
void Luminous::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_W)) {
		move_.z = 1.0f;
		// 移動量に速さを反映
		move_ = Math::Normalize(move_) * kSpeed;
		Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
		move_ = Math::TransformNormal(move_, rotMat);
	}
	Effect();
	for (auto& worldTransform : worldTransforms_) {
		// 移動
		worldTransform->translation_ += move_;
		// 行列の更新
		worldTransform->UpdateMatrix();
	}
}

void Luminous::DebugText() {
	ImGui::Begin("particle");
	ImGui::DragFloat3("[0].scale", &worldTransforms_[0]->scale_.x, 0.1f);
	ImGui::DragFloat3("[0].translation", &worldTransforms_[0]->translation_.x, 0.1f);
	ImGui::DragFloat3("[1].scale", &worldTransforms_[1]->scale_.x, 0.1f);
	ImGui::DragFloat3("[1].translation", &worldTransforms_[1]->translation_.x, 0.1f);
	ImGui::End();
}

// 描画
void Luminous::Draw() {
	for (auto& worldTranform : worldTransforms_) {
		model_->Draw(*worldTranform, *viewProjection_);
	}
}

// 飛んでいく方向のビュープロジェクションのセッター
void Luminous::SetDirectionView(ViewProjection* viewProjection) { directionViewProjection_ = viewProjection; }

// エフェクト
void Luminous::Effect() {
	theta_[0] += deltaTime;
	theta_[1] -= deltaTime;
	// theta_[0] と theta_[1] を配列として扱う
	for (int i = 0; i < 2; ++i) { // i = 0はtheta_[0]、i = 1はtheta_[1]
		float theta = theta_[i];

		// LissajousCurveに渡す係数セット
		std::array<Vector3, 3> factors = {
		    {{3.0f * theta, 4.0f * theta, theta}, {3.0f * theta, theta, 4.0f * theta}, {theta, 4.0f * theta, 3.0f * theta}}
        };

		// カラー成分（最後の引数）
		std::array<Vector3, 3> colors = {
		    {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}}
        };

		// 各要素を処理
		for (int j = 0; j < 3; ++j) {
			int index = 1 + i * 3 + j; // 配列のインデックスを計算
			worldTransforms_[index]->translation_ = Math::LissajousCurve(factors[j], worldTransforms_[0]->translation_, colors[j]);
		}
	}
}
