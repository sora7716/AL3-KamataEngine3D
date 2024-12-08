#include "Hexagon.h"
//#include "imgui.h"
#include <cmath>
#include <numbers>
#include <string>
#define rad pi_f / 180.0f

// 初期化
void Hexagon::Initialize(ViewProjection* viewProjection, const HexagonMaterial&& hexagonMaterial) {
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	hexagon_ = hexagonMaterial;
}

// 更新
void Hexagon::Update() {
	// 法線ベクトルの作成
	CreateNormal();
	for (int i = 0; i < kVertexNum; i++) {
		float theta = 60.0f * static_cast<float>(i);
		float angle = theta * rad;
		// 正面
		vertex[0][i].x = hexagon_.size.x * std::cosf(angle);
		vertex[0][i].y = hexagon_.size.y;
		vertex[0][i].z = hexagon_.size.z * std::sinf(angle);
		// 背面
		vertex[1][i].x = hexagon_.size.x * std::cosf(angle);
		vertex[1][i].y = -hexagon_.size.y;
		vertex[1][i].z = hexagon_.size.z * std::sinf(angle);
	}

	for (int i = 0; i < Surface; i++) {
		for (int j = 0; j < 6; j++) {
			screenVertex[i][j] = Conversion(rotate_, hexagon_.center, vertex[i][j]);
		}
	}
}

// デバックテキスト
void Hexagon::DebugText(const char* name) {
	(void*)name;
#ifdef DEBUG
	std::string centerText = static_cast<std::string>(name) + ".center";
	ImGui::DragFloat3(centerText.c_str(), &hexagon_.center.x, 0.1f);
	std::string radiusText = static_cast<std::string>(name) + ".size";
	ImGui::SliderFloat3(radiusText.c_str(), &hexagon_.size.x, 0.0f, 2.0f);
	std::string rotateText = static_cast<std::string>(name) + ".rotate";
	ImGui::DragFloat3(rotateText.c_str(), &rotate_.x, 0.1f);
#endif // DEBUG
}

// 描画
void Hexagon::Draw() {
	for (int i = 0; i < Surface; i++) {
		for (int j = 1; j < kVertexNum; j++) {
			PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertex[i][j - 1], screenVertex[i][j], hexagon_.color);
			PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertex[0][j], screenVertex[1][j], hexagon_.color);
		}
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertex[i][5], screenVertex[i][0], hexagon_.color);
	}
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertex[0][0], screenVertex[1][0], hexagon_.color);
}

// 衝突したとき
void Hexagon::OnCollision(bool isHit) {
	if (isHit) {
		hexagon_.color = RED;
	} else {
		hexagon_.color = WHITE;
	}
}

// 頂点のゲッター(local)
Vector3* Hexagon::GetVertex(int i) { return vertex[i]; }

// 頂点のゲッター(screen)
Vector3* Hexagon::GetScreenVertex(int i) { return screenVertex[i]; }

// 六角形の素材のゲッター
Shape::HexagonMaterial Hexagon::GetHexagonMaterial() { return hexagon_; }

// 回転のゲッター
Vector3 Hexagon::GetRotate() { return rotate_; }

// 法線ベクトルを作成
void Hexagon::CreateNormal() {
	// 面の法線を算出
	Vector3 v01 = GetVertex(0)[1] - GetVertex(0)[0];
	Vector3 v111 = GetVertex(0)[1] - GetVertex(1)[1];

	Vector3 v12 = GetVertex(0)[2] - GetVertex(0)[1];
	Vector3 v112 = GetVertex(0)[2] - GetVertex(1)[2];

	Vector3 v23 = GetVertex(0)[3] - GetVertex(0)[2];
	Vector3 v113 = GetVertex(0)[3] - GetVertex(1)[3];

	// 面の法線
	hexagon_.normal[0] = Math::Normalize(Math::Cross(v01, v111));
	hexagon_.normal[1] = Math::Normalize(Math::Cross(v12, v112));
	hexagon_.normal[2] = Math::Normalize(Math::Cross(v23, v113));
	hexagon_.normal[3] = Math::Normalize(Math::Cross(v01, v12));
}