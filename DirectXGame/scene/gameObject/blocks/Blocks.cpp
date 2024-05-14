#include "Blocks.h"
#include <cassert>
#include "calculate/Math.h"

void Blocks::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	texture_ = texture;
	viewProjection_ = viewProjection;
	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の横幅
	const float kBlockHeight = 2.0f;
	const float kBlockWidth = 2.0f;
	// 要素数の変更
	worldTransformBlocks_.resize(kNumBlockVirtical); // 縦の行(配列)
	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal); // 上で決めた行を横に伸ばす(配列)
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
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


