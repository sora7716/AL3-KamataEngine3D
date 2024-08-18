#include "WorldTransform.h"
#include "asset/math/Math.h"


void WorldTransform::UpdateMatrix() {
	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = Math::MakeAffineMatrix(scale_, rotation_, translation_);
	// 定数バッファに転送
	TransferMatrix();
}