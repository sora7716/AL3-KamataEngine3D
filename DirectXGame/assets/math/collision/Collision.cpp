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

// 球と球の衝突判定
bool Collision::IsCollision(const Shape::SphereMaterial& sphere1, const Shape::SphereMaterial& sphere2) {
	float distance = Math::Norm(sphere1.center - sphere2.center);
	float radiusSum = std::fabs(sphere1.radius) + std::fabs(sphere2.radius);
	if (distance <= radiusSum) {
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

// 球同士の当たり判定
bool operator==(const Shape::SphereMaterial& sphere1, const Shape::SphereMaterial& shpere2) { return Collision::GetInstance()->IsCollision(sphere1, shpere2); }

// AABB同士の当たり判定
bool operator==(const Shape::AABB& aabb1, const Shape::AABB& aabb2) { return Collision::GetInstance()->IsCollision(aabb1, aabb2); }
