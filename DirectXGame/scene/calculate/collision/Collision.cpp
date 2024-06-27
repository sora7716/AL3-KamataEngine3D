#include "Collision.h"

bool IsHit(const AABB& aabb1, const AABB& aabb2) {
	//X座標
	if (aabb1.min.x < aabb2.max.x && aabb1.max.x < aabb2.min.x) {
		return false;
	}
	if (aabb2.max.x < aabb1.min.x && aabb2.min.x < aabb1.max.x) {
		return false;
	}

	// Y座標
	if (aabb1.max.y > aabb2.min.y && aabb1.min.y > aabb2.max.y) {
		return false;
	}
	if (aabb2.max.y > aabb1.min.y && aabb2.min.y > aabb1.max.y) {
		return false;
	}

	// Z座標
	if (aabb1.min.z < aabb2.max.z && aabb1.max.z < aabb2.min.z) {
		return false;
	}
	if (aabb2.max.z < aabb1.min.z && aabb2.min.z < aabb1.max.z) {
		return false;
	}
	return true;
}