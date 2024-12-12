#include "Sphere.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <numbers>
#include <string>
using namespace std;

// 初期化
void Sphere::Initialize(const SphereMaterial&& sphereMaterial,ViewProjection* viewProjection) {
	sphere_ = sphereMaterial;
	viewProjection_ = viewProjection;
}

// 更新処理
void Sphere::Update() {}

#ifdef _DEBUG
// デバックテキスト
void Sphere::DebugText(const char* label) {
	string rotateLabel = string(label) + ".rotate";
	ImGui::DragFloat3(rotateLabel.c_str(), &sphere_.rotation.x, 0.1f);
	string centerLabel = string(label) + ".center";
	ImGui::DragFloat(centerLabel.c_str(), &sphere_.center.x, 0.01f);
	string radiusLabel = string(label) + ".radius";
	ImGui::DragFloat(radiusLabel.c_str(), &sphere_.radius, 0.01f);
}
#endif // _DEBUG

// 描画
void Sphere::Draw() {
	const uint32_t kSubdivision = 10;                          // 分割数
	const float kLatEvery = pi_f / float(kSubdivision);        // 経度分割1つ分の角度(θd)
	const float kLonEvery = 2.0f * pi_f / float(kSubdivision); // 緯度分割1つ分の角度(φd)

	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
		float lat = -pi_f / 2.0f + kLatEvery * latIndex; // θ
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // φ
			Vector3 a, b, c;                  // ローカル座標
			a = {sphere_.radius * cos(lat) * cos(lon), sphere_.radius * sin(lat), sphere_.radius * cos(lat) * sin(lon)};

			b = {sphere_.radius * cos(lat + kLatEvery) * cos(lon), sphere_.radius * sin(lat + kLatEvery), sphere_.radius * cos(lat + kLatEvery) * sin(lon)};

			c = {sphere_.radius * cos(lat + kLatEvery) * cos(lon + kLonEvery), sphere_.radius * sin(lat + kLatEvery), sphere_.radius * cos(lat + kLatEvery) * sin(lon + kLonEvery)};
			// スクリーン座標を求める
			screenA_ = Shape::Conversion(sphere_.rotation, sphere_.center, a);
			screenB_ = Shape::Conversion(sphere_.rotation, sphere_.center, b);
			screenC_ = Shape::Conversion(sphere_.rotation, sphere_.center, c);

			// 縦の線の描画
			PrimitiveDrawer::GetInstance()->DrawLine3d(screenA_, screenB_, color_);
			// 横の線の描画
			PrimitiveDrawer::GetInstance()->DrawLine3d(screenB_, screenC_, color_);
		}
	}
}

// カラーのセッター
void Sphere::SetColor(Vector4 color) { color_ = color; }

// スフィアの素材のゲッター
Sphere::SphereMaterial Sphere::GetSphereMaterial() const { return sphere_; }

// 球の素材のセッター
void Sphere::SetSphere(const SphereMaterial& material) { sphere_ = material; }