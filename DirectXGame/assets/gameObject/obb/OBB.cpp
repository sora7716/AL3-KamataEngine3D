#include "OBB.h"
#include "ViewProjection.h"
#include "PrimitiveDrawer.h"
#include "WinApp.h"
#include <string>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std;

// 初期化
void OBB::Initialize(ViewProjection* viewProjection, const Math::OBBMaterial&& obbMaterial) {
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	// OBBの値を設定
	obb_ = obbMaterial;
	// 角度
	rotate_ = obbMaterial.rotation;
}

// 更新
void OBB::Update() {
	// サイズを設定
	aabb_.min = -obb_.size;
	aabb_.max = obb_.size;
	viewport_ = Math::MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);
	MakeVertecies();                                                         // 頂点を作成
	Math::MakeOBBRotateMatrix(obb_.orientations, rotate_);                   // OBB用の回転行列を抽出
	worldMatrix_ = Math::MakeOBBWorldMatrix(obb_.orientations, obb_.center); // OBB用のワールド行列を作成
	// 正規化しておく
	for (int i = 0; i < 3; i++) {
		obb_.orientations[i] = Math::Normalize(obb_.orientations[i]);
	}
	// スクリーン座標に変換
	for (int i = 0; i < Math::kAABB2DNum; i++) {
		worldViewProjection_ = worldMatrix_ * (viewProjection_->matView * viewProjection_->matProjection);
		// 正規化デバイス座標系
		Vector3 ndcVertex_ = Math::Transform(localVertecies_[i].leftTop, worldViewProjection_);
		// スクリーン座標
		screenVertecies_[i].leftTop = Math::Transform(ndcVertex_, viewport_);
		// 正規化デバイス座標系
		ndcVertex_ = Math::Transform(localVertecies_[i].leftBottom, worldViewProjection_);
		// スクリーン座標
		screenVertecies_[i].leftBottom = Math::Transform(ndcVertex_, viewport_);
		// 正規化デバイス座標系
		ndcVertex_ = Math::Transform(localVertecies_[i].rightTop, worldViewProjection_);
		// スクリーン座標
		screenVertecies_[i].rightTop = Math::Transform(ndcVertex_, viewport_);
		// 正規化デバイス座標系
		ndcVertex_ = Math::Transform(localVertecies_[i].rightBottom, worldViewProjection_);
		// スクリーン座標
		screenVertecies_[i].rightBottom = Math::Transform(ndcVertex_, viewport_);
	}
}

// デバックテキスト
void OBB::DebagText(const char* type) {
	string sizeMoji = string(type) + "size";
	ImGui::SliderFloat3(sizeMoji.c_str(), &obb_.size.x, 0.0f, 3.0f);
	string rotateMoji = string(type) + ".rotation";
	ImGui::DragFloat3(rotateMoji.c_str(), &rotate_.x, 0.01f);
	string translationMoji = string(type) + ".translation";
	ImGui::DragFloat3(translationMoji.c_str(), &obb_.center.x, 0.01f);
}

// 描画
void OBB::Draw() {
	// 正面と背面の生成
	for (int i = 0; i < Math::kAABB2DNum; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].leftTop, screenVertecies_[i].rightTop, obb_.color);
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].rightTop, screenVertecies_[i].rightBottom, obb_.color);
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].rightBottom, screenVertecies_[i].leftBottom, obb_.color);
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].leftBottom, screenVertecies_[i].leftTop, obb_.color);
	}
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].leftTop, screenVertecies_[1].leftTop, obb_.color);
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].rightTop, screenVertecies_[1].rightTop, obb_.color);
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].leftBottom, screenVertecies_[1].leftBottom, obb_.color);
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].rightBottom, screenVertecies_[1].rightBottom, obb_.color);
}

// ワールドマトリックス逆行列のゲッター
Matrix4x4 OBB::GetOBBWorldMatrixInvers() const {
	Matrix4x4 obbWorldMatrixInvers = ~worldMatrix_;
	return obbWorldMatrixInvers;
}

// サイズのゲッター
Vector3 OBB::GetSize() const { return obb_.size; }

// OBBのマテリアルのゲッター
Math::OBBMaterial OBB::GetOBBMaterial() const { return obb_; }

void OBB::OnCollision(bool isHit) {
	if (isHit) {
		obb_.color = RED;
	} else {
		obb_.color = WHITE;
	}
}

// 頂点を作成
void OBB::MakeVertecies() {
	localVertecies_[0].leftTop = {aabb_.min.x, aabb_.max.y, aabb_.min.z};
	localVertecies_[0].rightTop = {aabb_.max.x, aabb_.max.y, aabb_.min.z};
	localVertecies_[0].leftBottom = {aabb_.min.x, aabb_.min.y, aabb_.min.z};
	localVertecies_[0].rightBottom = {aabb_.max.x, aabb_.min.y, aabb_.min.z};

	localVertecies_[1].leftTop = {aabb_.min.x, aabb_.max.y, aabb_.max.z};
	localVertecies_[1].rightTop = {aabb_.max.x, aabb_.max.y, aabb_.max.z};
	localVertecies_[1].leftBottom = {aabb_.min.x, aabb_.min.y, aabb_.max.z};
	localVertecies_[1].rightBottom = {aabb_.max.x, aabb_.min.y, aabb_.max.z};
}
