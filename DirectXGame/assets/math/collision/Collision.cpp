#include "Collision.h"
#include "PrimitiveDrawer.h"
#include "assets/math/Math.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

// 球と球の衝突判定
bool Collision::IsCollision(const Vector3& posA, const Vector3& posB, float radiusA, float radiusB) {
	float distance = Math::Length(posA - posB);
	float radiusSum = radiusA + radiusB;
	if (distance * distance <= radiusSum) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(const AABB& aabb1, const AABB& aabb2) {

	// X座標の当たってない判定
	if (aabb1.min.x < aabb2.max.x && aabb1.max.x < aabb2.min.x) {
		return false;
	}
	if (aabb2.max.x < aabb1.min.x && aabb2.min.x < aabb1.max.x) {
		return false;
	}

	// Y座標の当たってない判定
	if (aabb1.max.y > aabb2.min.y && aabb1.min.y > aabb2.max.y) {
		return false;
	}
	if (aabb2.max.y > aabb1.min.y && aabb2.min.y > aabb1.max.y) {
		return false;
	}

	// Z座標の当たってない判定
	if (aabb1.min.z < aabb2.max.z && aabb1.max.z < aabb2.min.z) {
		return false;
	}
	if (aabb2.max.z < aabb1.min.z && aabb2.min.z < aabb1.max.z) {
		return false;
	}

	return true;
}

// 線を表示
void Collision::DrawLine(Vector3 worldPos, Vector3 size, ViewProjection* viewProjection, Vector4 color) { 
	//線を描画するようのビュープロジェクションを設定
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection);
	//線を描画
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - size, worldPos + size, color);
}

// 3Dの箱を作成
void Collision::DrawBox(Vector3 worldPos, Vector3 size, ViewProjection* viewProjection) {
	// 線を描画するようのビュープロジェクションを設定
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection);
	// 線を描画
	
	//下端
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, 0.0f, 0.0f), worldPos + Vector3(size.x / 2.0f, 0.0f, 0.0f), {1.0f, 0.0f, 0.0f, 1.0f});//正面
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos + Vector3(size.x / 2.0f, 0.0f, 0.0f), worldPos + Vector3(size.x / 2.0f, 0.0f, size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 右側
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, 0.0f, 0.0f), worldPos + Vector3(-size.x / 2.0f, 0.0f, size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 左側
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, 0.0f, -size.z), worldPos + Vector3(size.x / 2.0f, 0.0f, size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 背面
	//上端
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, -size.y, 0.0f), worldPos + Vector3(size.x / 2.0f, size.y, 0.0f), {1.0f, 0.0f, 0.0f, 1.0f});//正面
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos + Vector3(size.x / 2.0f, size.y, 0.0f), worldPos + Vector3(size.x / 2.0f, size.y, size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 右側
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, -size.y, 0.0f), worldPos + Vector3(-size.x / 2.0f, size.y, size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 左側
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, -size.y, -size.z), worldPos + Vector3(size.x / 2.0f, size.y, size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 背面
	//右端
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos + Vector3(size.x / 2.0f,size.y, 0.0f), worldPos + Vector3(size.x/2.0f, 0.0f, 0.0f), {1.0f, 0.0f, 0.0f, 1.0f});//正面
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos + Vector3(size.x / 2.0f, size.y, size.z), worldPos + Vector3(size.x / 2.0f, 0.0f, size.z), {1.0f, 0.0f, 0.0f, 1.0f});//背面
	//左端
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, -size.y, 0.0f), worldPos - Vector3(size.x / 2.0f, 0.0f, 0.0f), {1.0f, 0.0f, 0.0f, 1.0f});//正面
	PrimitiveDrawer::GetInstance()->DrawLine3d(worldPos - Vector3(size.x / 2.0f, -size.y, -size.z), worldPos - Vector3(size.x / 2.0f, 0.0f, -size.z), {1.0f, 0.0f, 0.0f, 1.0f}); // 背面

}
