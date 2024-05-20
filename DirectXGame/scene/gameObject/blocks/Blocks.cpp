#include "Blocks.h"
#include <cassert>
#include "calculate/Math.h"

//ブロックの初期化
void Blocks::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection, MapChipField* mapChipField) {
	assert(model);
	model_ = model;
	texture_ = texture;
	viewProjection_ = viewProjection;
	assert(mapChipField);
	mapChipField_ = mapChipField;
	// 要素数
	uint32_t numBlockVertical   = mapChipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// ブロック1個分の横幅
	const float kBlockHeight = mapChipField_->GetBlockHeight();
	const float kBlockWidth  = mapChipField_->GetBlockWidth();
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
			// 初期化↓
			if (i % 2 == 1 && j % 2 == 1 || i % 2 == 0 && j % 2 == 0) {
				worldTransformBlocks_[i][j] = new WorldTransform();             // ブロックの生成
				worldTransformBlocks_[i][j]->Initialize();                      // ブロックの初期化
				worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;  // 横にj分ずらす
				worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i; // 縦にi分ずらす
			}
			// 初期化↑
		}
	}
}

//ブロックの更新処理
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

//ブロックの描画
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


