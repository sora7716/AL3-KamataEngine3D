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
	model_ = move(model);             // モデルを受け取る
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	worldTransforms_.resize(row);
	for (int i = 0; i < row; i++) {
		WorldTransform* worldTranform = new WorldTransform();//ワールドトランスフォーム(単体)を生成
		worldTranform->Initialize();//生成したワールドトランスフォームを初期化
		worldTranform->rotation_.x = pi_v<float> / 2.0f;//角度を設定
		worldTranform->translation_.z = 20.0f;//位置を設定
		worldTranform->translation_.x = radius_ * cosf(pi_v<float> / 3.0f * static_cast<float>(i)); // 極座標から直交座標を求める
		worldTranform->translation_.y = radius_ * sinf(pi_v<float> / 3.0f * static_cast<float>(i)); // 極座標から直交座標を求める
		worldTransforms_[i] = worldTranform;//ワールドトランスフォーム(複数)に代入
	}
}

// 更新
void Hexagon::Update() {
	ImGui::Begin("hexagon");
	ImGui::DragFloat("radius", &radius_, 0.1f);
	ImGui::End();
	worldTransforms_[1]->translation_.x = radius_ * cosf(pi_v<float> / 3.0f * static_cast<float>(1)); // 極座標から直交座標を求める
	worldTransforms_[1]->translation_.y = radius_ * sinf(pi_v<float> / 3.0f * static_cast<float>(1)); // 極座標から直交座標を求める
	for (auto &worldTransform : worldTransforms_) {
		worldTransform->UpdateMatrix(); // 行列の更新
	}
}

// 描画
void Hexagon::Draw() {
	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(*worldTransform, *viewProjection_);
	}
}
