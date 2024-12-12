#include "OBB.h"
#include <string>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std;

// 初期化
void OBB::Initialize(const OBBMaterial&& obbMaterial,ViewProjection* viewProjection) {
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
	MakeVertecies();// 頂点を作成
	// スクリーン座標に変換
	for (int i = 0; i < Math::kAABB2DNum; i++) {

		// スクリーン座標
		screenVertecies_[i].leftTop = Conversion(rotate_, obb_.center, localVertecies_[i].leftTop, obb_.orientations);
		screenVertecies_[i].rightTop = Conversion(rotate_, obb_.center, localVertecies_[i].rightTop, obb_.orientations);
		screenVertecies_[i].leftBottom = Conversion(rotate_, obb_.center, localVertecies_[i].leftBottom, obb_.orientations);
		screenVertecies_[i].rightBottom = Conversion(rotate_, obb_.center, localVertecies_[i].rightBottom, obb_.orientations);
	}
	// 正規化しておく
	for (int i = 0; i < 3; i++) {
		obb_.orientations[i] = Math::Normalize(obb_.orientations[i]);
	}
}

// デバックテキスト
void OBB::DebagText(const char* label) {
	(void)label;
#ifdef _DEBUG
	string sizeMoji = string(label) + "size";
	ImGui::SliderFloat3(sizeMoji.c_str(), &obb_.size.x, 0.0f, 3.0f);
	string rotateMoji = string(label) + ".rotation";
	ImGui::DragFloat3(rotateMoji.c_str(), &rotate_.x, 0.01f);
	string translationMoji = string(label) + ".translation";
	ImGui::DragFloat3(translationMoji.c_str(), &obb_.center.x, 0.01f);
#endif // _DEBUG
}

// 描画
void OBB::Draw() {
	// 正面と背面の生成
	for (int i = 0; i < Math::kAABB2DNum; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].leftTop, screenVertecies_[i].rightTop, color_);
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].rightTop, screenVertecies_[i].rightBottom, color_);
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].rightBottom, screenVertecies_[i].leftBottom, color_);
		PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[i].leftBottom, screenVertecies_[i].leftTop, color_);
	}
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].leftTop, screenVertecies_[1].leftTop, color_);
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].rightTop, screenVertecies_[1].rightTop, color_);
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].leftBottom, screenVertecies_[1].leftBottom, color_);
	PrimitiveDrawer::GetInstance()->DrawLine3d(screenVertecies_[0].rightBottom, screenVertecies_[1].rightBottom, color_);
}

// ワールドマトリックス逆行列のゲッター
Matrix4x4 OBB::GetOBBWorldMatrixInvers() const {
	Matrix4x4 obbWorldMatrixInvers = ~worldMatrix_;
	return obbWorldMatrixInvers;
}

// サイズのゲッター
Vector3 OBB::GetSize() const { return obb_.size; }

// OBBのマテリアルのゲッター
Shape::OBBMaterial OBB::GetOBBMaterial() const { return obb_; }

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
