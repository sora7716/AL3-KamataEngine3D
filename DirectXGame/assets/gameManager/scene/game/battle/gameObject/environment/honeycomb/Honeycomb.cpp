#include "Honeycomb.h"
#include "ImGuiManager.h"
#include "assets/failLoad/map/MapChipField.h"
#include "assets/math/Aithmetic.h"
#include "cell/NormalCell.h"
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
	cells_.resize(kHorizontal);                              // セルの横幅を設定
	worldTransform_.Initialize();                            // 六角形の親の初期化
	worldTransform_.translation_ = {-8.6f, -2.6f, 5.8f};     // 初期位置
	collider_.rotation_ = {0.0f, pi_f / 2.0f, 0.0f};         // コライダーの角度
	collider_.scale_ = {radius.x, 1.0f, radius.z};           // コライダーのサイズ
	for (int i = 0; i < kHorizontal; i++) {
		worldTransforms_[i].resize(vertical);
		cells_[i].resize(vertical); // セルの縦幅を設定
		for (int j = 0; j < vertical; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				NormalCell* cell = new NormalCell();
				worldTransform->Initialize();
				worldTransform->scale_ = radius;
				worldTransform->translation_.x = (j + 0.5f * (i % 2)) * radius.x * sqrt(3.0f); // x座標の計算
				worldTransform->translation_.z = i * (1.5f * radius.z);                        // z座標の計算
				worldTransform->parent_ = &worldTransform_;
				cell->Initialize(model, viewProjection_);
				cell->SetScale(worldTransform->scale_);
				cell->SetRotate(worldTransform->rotation_);
				cell->SetTranslate(worldTransform->translation_);
				cell->SetParent(&worldTransform_);
				worldTransforms_[i][j] = worldTransform; // 代入
				cells_[i][j] = cell;
			}
		}
	}
}

// 更新
void Honeycomb::Update() {
#ifdef _DEBUG
	ImGui::Begin("Honeycomb");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f, 0.0f, 30.0f);
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

	for (auto piece : cells_) {
		for (auto& cell : piece) {
			if (cell) {
				cell->Update(); // 更新
			}
		}
	}
}

// 描画
void Honeycomb::Draw() {
	for (auto piece : cells_) {
		for (auto& cell : piece) {
			if (cell) {
				cell->Draw();
			}
		}
	}
}

// ワイヤーモデルの表示
void Honeycomb::DrawWire() {
	for (int i = 0; i < cells_.size(); i++) {
		for (int j = 0; j < cells_[i].size(); j++) {
			if (cells_[i][j]) {
				Hexagon* wireFrame = new Hexagon();
				wireFrame = cells_[i][j]->GetWireFrame();
				wireFrame->SetScale(collider_.scale_);
				wireFrame->SetRotate(collider_.rotation_);
				wireFrame->SetTranslate({worldTransforms_[i][j]->matWorld_.m[3][0], worldTransforms_[i][j]->matWorld_.m[3][1], worldTransforms_[i][j]->matWorld_.m[3][2]});
				cells_[i][j]->SetWireModel(wireFrame);
			}
		}
	}
	for (auto piece : cells_) {
		for (auto& cell : piece) {
			if (cell) {
				cell->GetWireFrame()->Draw();
			}
		}
	}
}

// 普通のセルのゲッター
std::vector<std::vector<BaseCell*>> Honeycomb::GetWireFrame() { return cells_; }
