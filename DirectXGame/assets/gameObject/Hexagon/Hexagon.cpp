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
	model_ = move(model);                   // モデルを受け取る
	viewProjection_ = viewProjection;       // ビュープロジェクションを受け取る
	polar_.radian = pi_v<float> / 3.0f;     // 60度を弧度法に直した
	polar_.radius = 1.0f;                   // 半径
	polar_.diameter = polar_.radius * 2.0f; // 直径
	worldTransforms_.resize(kLayer);//層の数を設定
	parent_ = new WorldTransform();//六角形の親の生成
	parent_->Initialize();//六角形の親の初期化
	for (int i = 0; i < kLayer; i++) {
		numPieces = (i == 0) ? 1 : (6 * i); // 1層目は1つのピース、2層目以降は6*iのピース
		worldTransforms_[i].resize(numPieces);

		float radianStep = 2.0f * pi_v<float> / numPieces; // 各層のピースに基づいた角度
		for (int j = 0; j < numPieces; j++) {
			WorldTransform* worldTransform = new WorldTransform();                       // ワールドトランスフォーム(単体)を生成
			worldTransform->Initialize();                                                // 生成したワールドトランスフォームを初期化
			worldTransform->rotation_.x = pi_v<float> / 2.0f;                            // 角度を設定
			worldTransform->translation_.z = 20.0f;                                      // z軸の設定
			worldTransform->translation_.x = polar_.diameter * i * cosf(radianStep * j); // 極座標から直交座標を求める
			worldTransform->translation_.y = polar_.diameter * i * sinf(radianStep * j); // 極座標から直交座標を求める
			worldTransforms_[i][j] = worldTransform;                                     // ワールドトランスフォーム(複数)に代入
			worldTransforms_[i][j]->parent_ = parent_;
			if (i == 0) {
				break; // 中心の六角形だったら抜ける
			}
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
	parent_->UpdateMatrix();//親の行列の更新
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
