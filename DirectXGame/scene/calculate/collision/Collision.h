#pragma once
#include <Vector3.h>
// AABB
typedef struct AABB {
	Vector3 min;
	Vector3 max;
} AABB;

bool IsHit(const AABB& aabb1, const AABB& aabb2);
//class Collision {};
