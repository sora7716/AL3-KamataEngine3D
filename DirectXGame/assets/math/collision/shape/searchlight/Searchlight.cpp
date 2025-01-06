#include "Searchlight.h"

// 初期化
void Searchlight::Initialize(const SerchlightMaterial&& serchlightMaterial, ViewProjection* viewProjection) {
	serchlightMaterial_ = serchlightMaterial;
	viewProjection_ = viewProjection;
	// 度数法から弧度法に直す
	serchlightMaterial_.direction = radian(serchlightMaterial_.direction);
	serchlightMaterial_.range = radian(serchlightMaterial_.range);
}

// 更新
void Searchlight::Update() {
	for (int i = 0; i < kSubdivisions; i++) {
		const float halfRange = serchlightMaterial_.range / 2.0f;
		float angle1 = serchlightMaterial_.direction - halfRange + serchlightMaterial_.range * (float(i) / kSubdivisions);
		float angle2 = serchlightMaterial_.direction - halfRange + serchlightMaterial_.range * (float(i + 1) / kSubdivisions);
		beginPos_[0][i] = {
		    .x = std::cos(angle1) * serchlightMaterial_.radius,
		    .y = std::sin(angle1) * serchlightMaterial_.radius,
		};
		endPos_[0][i] = {
		    .x = std::cos(angle2) * serchlightMaterial_.radius,
		    .y = std::sin(angle2) * serchlightMaterial_.radius,
		};
		beginPos_[0][i] = {
		    .x = std::sin(angle1) * serchlightMaterial_.radius,
		    .z = std::cos(angle1) * serchlightMaterial_.radius,
		};
		endPos_[0][i] = {
		    .x = std::sin(angle2) * serchlightMaterial_.radius,
		    .z = std::cos(angle2) * serchlightMaterial_.radius,
		};
		for (int j = 0; j < 2; j++) {
			screenBeginPos_[j][i] = Shape::Conversion(rotation_, serchlightMaterial_.center, beginPos_[j][i]);
			screenEndPos_[j][i] = Shape::Conversion(rotation_, serchlightMaterial_.center, endPos_[j][i]);
		}
	}
}

// デバックテキスト
void Searchlight::DebugText(const char* label) {
	std::string serchlightLabel = std::string(label) + ".center";
#ifdef _DEBUG
	ImGui::DragFloat3(serchlightLabel.c_str(), &serchlightMaterial_.center.x, 0.1f);
	serchlightLabel = std::string(label) + ".rotation";
	ImGui::DragFloat3(serchlightLabel.c_str(), &rotation_.x, 0.1f);
	serchlightLabel = std::string(label) + ".radius";
	ImGui::DragFloat(serchlightLabel.c_str(), &serchlightMaterial_.radius, 0.1f);
	serchlightLabel = std::string(label) + ".direction";
	ImGui::DragFloat(serchlightLabel.c_str(), &serchlightMaterial_.direction, 0.1f, 0.0f, 2.0f * pi_f);
	serchlightLabel = std::string(label) + ".range";
	ImGui::DragFloat(serchlightLabel.c_str(), &serchlightMaterial_.range, 0.1f, 0.0f, 2.0 * pi_f);
#endif // _DEBUG
}

// 描画
void Searchlight::Draw() {
#ifdef _DEBUG
	for (int i = 0; i < kSubdivisions; i++) {
		for (int j = 0; j < 2; j++) {
			PrimitiveDrawer::GetInstance()->DrawLine3d(screenBeginPos_[j][i], screenEndPos_[j][i], WHITE);
		}
	}
	for (int i = 0; i < 2; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(serchlightMaterial_.center, screenBeginPos_[i][kSubdivisions - 1], WHITE);
		PrimitiveDrawer::GetInstance()->DrawLine3d(serchlightMaterial_.center, screenBeginPos_[i][0], WHITE);
	}
#endif // _DEBUG
}
