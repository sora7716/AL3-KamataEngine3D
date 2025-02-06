#include "OBB.h"
#include "ImGuiManager.h"
#include <string>
using namespace std;

// 初期化
void OBB::Initialize(const OBBMaterial&& obbMaterial, ViewProjection* viewProjection) {
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	// OBBの値を設定
	obb_ = obbMaterial;
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection_);
}

// 更新
void OBB::Update() {
	Shape::Update();
	// サイズを設定
	aabb_.min = -obb_.size;
	aabb_.max = obb_.size;
	MakeVertecies(); // 頂点を作成
	// スクリーン座標に変換
	for (int i = 0; i < Math::kAABB2DNum; i++) {

		// スクリーン座標
		screenVertecies_[i].leftTop = Conversion(obb_.rotation, obb_.center, localVertecies_[i].leftTop, obb_.orientations, parentMatWorld_);
		screenVertecies_[i].rightTop = Conversion(obb_.rotation, obb_.center, localVertecies_[i].rightTop, obb_.orientations, parentMatWorld_);
		screenVertecies_[i].leftBottom = Conversion(obb_.rotation, obb_.center, localVertecies_[i].leftBottom, obb_.orientations, parentMatWorld_);
		screenVertecies_[i].rightBottom = Conversion(obb_.rotation, obb_.center, localVertecies_[i].rightBottom, obb_.orientations, parentMatWorld_);
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
	ImGui::DragFloat3(rotateMoji.c_str(), &obb_.rotation.x, 0.01f);
	string translationMoji = string(label) + ".translation";
	ImGui::DragFloat3(translationMoji.c_str(), &obb_.center.x, 0.01f);
#endif // _DEBUG
}

// 描画
void OBB::Draw() {
#ifdef _DEBUG
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
#endif // _DEBUG
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

// AABBのゲッター
Shape::AABB OBB::GetAABB() {
	return {
	    obb_.center + aabb_.min,
	    obb_.center + aabb_.max,
	};
}

// スケールのセッター
void OBB::SetScale(const Vector3 scale) { obb_.size = scale; }

// 回転のゲッター
void OBB::SetRotate(const Vector3 rotate) { obb_.rotation = rotate; }

// 現在位置のセッター
void OBB::SetPosition(const Vector3 position) { obb_.center = position; }

// 親のワールド行列のセッター
void OBB::SetWorldMatWorld(const Matrix4x4* parentMatWorld) {
	if (parentMatWorld_ == nullptr) {
		parentMatWorld_ = new Matrix4x4();
	}
	*parentMatWorld_ = *parentMatWorld;
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
