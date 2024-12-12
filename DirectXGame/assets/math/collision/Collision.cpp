#include "Collision.h"
#include "PrimitiveDrawer.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/math/Math.h"

// インスタンスのゲッター
Collision* Collision::GetInstance() {
	static Collision instance;
	return &instance;
}

// スフィアのインスタンスのゲッター
Sphere* Collision::GetSphereInstance() {
	static Sphere instance;
	return &instance;
}
// OBBのインスタンスのゲッター
OBB* Collision::GetOBBInstance() {
	static OBB instance;
	return &instance;
}

// 六角柱のインスタンスのゲッター
Hexagon* Collision::GetHexagonInstance() {
	static Hexagon instance;
	return &instance;
}

// 球と球の衝突判定
bool Collision::IsCollision(const Vector3& posA, const Vector3& posB, float radiusA, float radiusB) {
	float distance = Math::Norm(posA - posB);
	float radiusSum = radiusA + radiusB;
	if (distance * distance <= radiusSum) {
		return true;
	}
	return false;
}

bool Collision::IsCollision(const Shape::AABB& aabb1, const Shape::AABB& aabb2) {

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
