#include "Blocks.h"
#include "Model.h"
#include "calculate/Math.h"
#include "gameObject/mapChipField/MapChipField.h"
#include <cassert>

// ブロックの初期化
void Blocks::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection, MapChipField* mapChipField) {
	assert(model);
	model_ = model;
	texture_ = texture;
	viewProjection_ = viewProjection;
	assert(mapChipField);
	mapChipField_ = mapChipField;
	// 要素数
	uint32_t numBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	worldTransformBlocks_.resize(numBlockVertical);
	for (uint32_t i = 0; i < numBlockVertical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	// キューブの生成
	for (uint32_t i = 0; i < numBlockVertical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

// ブロックの更新処理
void Blocks::Update() {
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			worldTransformBlock->UpdateMatrix(); // アフィン変換
		}
	}
}

// ブロックの描画
void Blocks::Draw() {
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			model_->Draw(*worldTransformBlock, *(viewProjection_), texture_); // ブロックの描画
		}
	}
}
