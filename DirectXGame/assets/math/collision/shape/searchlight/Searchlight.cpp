#include "Searchlight.h"

// 初期化
void Searchlight::Initialize(const SerchlightMaterial&& serchlightMaterial, ViewProjection* viewProjection) {
	serchlightMaterial_ = serchlightMaterial;
	viewProjection_ = viewProjection;
}

// 更新
void Searchlight::Update() {
	for (int i = 0; i < kSubdivisions; i++) {
		float theta1 = std::lerp(serchlightMaterial_.beginAngle, serchlightMaterial_.endAngle, float(i / kSubdivisions));
		float theta2 = std::lerp(serchlightMaterial_.beginAngle, serchlightMaterial_.endAngle, float(i + 1 / kSubdivisions));
		beginPos_[i] = {serchlightMaterial_.radius * std::cos(theta1), serchlightMaterial_.radius * std::sin(theta1)};
		endPos_[i] = {serchlightMaterial_.radius * std::cos(theta2), serchlightMaterial_.radius * std::sin(theta2)};
	}
}

// 描画
void Searchlight::Draw() {
	for (int i = 0; i < kSubdivisions; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(beginPos_[i], endPos_[i], WHITE);
	}
	PrimitiveDrawer::GetInstance()->DrawLine3d(beginPos_[0], serchlightMaterial_.center, WHITE);
	PrimitiveDrawer::GetInstance()->DrawLine3d(beginPos_[kSubdivisions - 1], serchlightMaterial_.center, WHITE);
}
