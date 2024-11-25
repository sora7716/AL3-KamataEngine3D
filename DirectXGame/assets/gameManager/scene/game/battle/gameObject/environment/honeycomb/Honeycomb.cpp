#include "Honeycomb.h"
#include "ImGuiManager.h"
#include "assets/failLoad/map/MapChipField.h"
#include "assets/math/Aithmetic.h"
#include <cassert>

// コンストラクタ
Honeycomb::Honeycomb(MapChipField* mapChipField) : mapChipField_(mapChipField) {}

// 初期化
void Honeycomb::Initialize(Model* model, ViewProjection* viewProjection) {
	model_ = std::move(model);                               // モデルを受け取る
	viewProjection_ = viewProjection;                        // ビュープロジェクションを受け取る
	Vector3 radius = MapChipField::kHexagonRadius;           // 半径
	int32_t kHorizontal = MapChipField::kNumBlockHorizontal; // 横幅
	int32_t vertical = MapChipField::kNumBlockVertical;      // 縦幅
	worldTransforms_.resize(kHorizontal);                    // 横幅を設定
	worldTransform_.Initialize();                            // 六角形の親の初期化
	worldTransform_.translation_ = {-8.6f, -2.6f, 5.8f};     // 初期位置
	for (int i = 0; i < kHorizontal; i++) {
		worldTransforms_[i].resize(vertical);
		for (int j = 0; j < vertical; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransform->scale_ = radius;
				worldTransform->translation_.x = (j + 0.5f * (i % 2)) * radius.x * sqrt(3.0f); // x座標の計算
				worldTransform->translation_.z = i * (1.5f * radius.z);                        // z座標の計算
				worldTransform->parent_ = &worldTransform_;
				worldTransforms_[i][j] = worldTransform; // 代入
			}
		}
	}
}

// 更新
void Honeycomb::Update() {
#ifdef _DEBUG
	ImGui::Begin("Hexagon");
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // DEBUG
	for (auto piece : worldTransforms_) {
		for (auto& worldTransform : piece) {
			if (worldTransform) {
				worldTransform->UpdateMatrix(); // 行列の更新
			}
		}
	}
	worldTransform_.UpdateMatrix(); // 親の行列の更新
}

// 描画
void Honeycomb::Draw() {
	for (auto piece : worldTransforms_) {
		for (auto& worldTransform : piece) {
			if (worldTransform) {
				model_->Draw(*worldTransform, *viewProjection_);
			}
		}
	}
}