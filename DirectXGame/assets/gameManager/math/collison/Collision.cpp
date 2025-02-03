#define NOMINMAX
#include "Collision.h"
#include "PrimitiveDrawer.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/gameManager/math/Math.h"
#include <algorithm>

// インスタンスのゲッター
Collision* Collision::GetInstance() {
	static Collision instance;
	return &instance;
}

// 球
bool Collision::IsCollision(const Shape::SphereMaterial& sphere1, const Shape::SphereMaterial& sphere2) {
	float distance = Math::Norm(sphere1.center - sphere2.center);
	float radiusSum = std::fabs(sphere1.radius) + std::fabs(sphere2.radius);
	if (distance <= radiusSum) {
		return true;
	}
	return false;
}

// AABB
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

// OBB
bool Collision::IsCollision(const Shape::OBBMaterial& obb1, const Shape::OBBMaterial& obb2) {
	// 分割軸の数
	Vector3 separateAxes[15];
	// 面の法線
	/*ターゲット*/
	separateAxes[0] = obb1.orientations[0];
	separateAxes[1] = obb1.orientations[1];
	separateAxes[2] = obb1.orientations[2];
	/*ターゲットではないほう*/
	separateAxes[3] = obb2.orientations[0];
	separateAxes[4] = obb2.orientations[1];
	separateAxes[5] = obb2.orientations[2];
	// 9つの辺のクロス積
	separateAxes[6] = Math::Cross(obb1.orientations[0], obb2.orientations[0]);
	separateAxes[7] = Math::Cross(obb1.orientations[0], obb2.orientations[1]);
	separateAxes[8] = Math::Cross(obb1.orientations[0], obb2.orientations[2]);
	separateAxes[9] = Math::Cross(obb1.orientations[1], obb2.orientations[0]);
	separateAxes[10] = Math::Cross(obb1.orientations[1], obb2.orientations[1]);
	separateAxes[11] = Math::Cross(obb1.orientations[1], obb2.orientations[2]);
	separateAxes[12] = Math::Cross(obb1.orientations[2], obb2.orientations[0]);
	separateAxes[13] = Math::Cross(obb1.orientations[2], obb2.orientations[1]);
	separateAxes[14] = Math::Cross(obb1.orientations[2], obb2.orientations[2]);

	// 半分のベクトル
	/*obb1*/
	Vector3 obb1Direction[3]{
	    obb1.orientations[0] * obb1.size.x,
	    obb1.orientations[1] * obb1.size.y,
	    obb1.orientations[2] * obb1.size.z,
	};
	/*obb2*/
	Vector3 obb2Direction[3]{
	    obb2.orientations[0] * obb2.size.x,
	    obb2.orientations[1] * obb2.size.y,
	    obb2.orientations[2] * obb2.size.z,
	};

	// 頂点の数
	const int kCornerNum = 8;

	// 点(頂点)
	Vector3 targetCorners[kCornerNum] = {
	    obb1.center + obb1Direction[0] + obb1Direction[1] + obb1Direction[2], // 背面の右上
	    obb1.center + obb1Direction[0] + obb1Direction[1] - obb1Direction[2], // 正面の右上
	    obb1.center + obb1Direction[0] - obb1Direction[1] + obb1Direction[2], // 背面の右下
	    obb1.center + obb1Direction[0] - obb1Direction[1] - obb1Direction[2], // 正面の右下
	    obb1.center - obb1Direction[0] + obb1Direction[1] + obb1Direction[2], // 背面の左上
	    obb1.center - obb1Direction[0] + obb1Direction[1] - obb1Direction[2], // 正面の左上
	    obb1.center - obb1Direction[0] - obb1Direction[1] + obb1Direction[2], // 背面の左下
	    obb1.center - obb1Direction[0] - obb1Direction[1] - obb1Direction[2], // 正面の左下
	};
	Vector3 obbCorners[kCornerNum] = {
	    obb2.center + obb2Direction[0] + obb2Direction[1] + obb2Direction[2], // 背面の右上
	    obb2.center + obb2Direction[0] + obb2Direction[1] - obb2Direction[2], // 正面の右上
	    obb2.center + obb2Direction[0] - obb2Direction[1] + obb2Direction[2], // 背面の右下
	    obb2.center + obb2Direction[0] - obb2Direction[1] - obb2Direction[2], // 正面の右下
	    obb2.center - obb2Direction[0] + obb2Direction[1] + obb2Direction[2], // 背面の左上
	    obb2.center - obb2Direction[0] + obb2Direction[1] - obb2Direction[2], // 正面の左上
	    obb2.center - obb2Direction[0] - obb2Direction[1] + obb2Direction[2], // 背面の左下
	    obb2.center - obb2Direction[0] - obb2Direction[1] - obb2Direction[2], // 正面の左下
	};
	// 中心点間のベクトル
	Vector3 centerToCenter = obb1.center - obb2.center;

	// 当たったかの判定
	bool isHit = true;

	// 当たり判定の計算
	for (const auto& separateAxis : separateAxes) {
		float minTarget = (std::numeric_limits<float>::max)();
		float maxTarget = (std::numeric_limits<float>::lowest)();
		float minOBB = minTarget;
		float maxOBB = maxTarget;
		for (auto cornerIndex = 0; cornerIndex < kCornerNum; cornerIndex++) {
			float targetDistance = Math::Dot(targetCorners[cornerIndex], separateAxis);
			minTarget = (std::min)(targetDistance, minTarget);
			maxTarget = (std::max)(targetDistance, maxTarget);
			float obbDistance = Math::Dot(obbCorners[cornerIndex], separateAxis);
			minOBB = (std::min)(obbDistance, minOBB);
			maxOBB = (std::max)(obbDistance, maxOBB);
		}
		// それぞれを射影した範囲長の合計を求める
		float sumSpan = maxTarget - minTarget + maxOBB - minOBB;
		// 最大範囲を求める
		float longSpan = (std::max)(maxTarget, maxOBB) - (std::min)(minTarget, minOBB);
		// 分離軸が見つかる判定
		if (sumSpan < longSpan) {
			isHit = false;
		}
	}
	return isHit;
}

// OBBと六角柱
bool Collision::IsCollision(const Shape::HexagonMaterial& hexagon, const Shape::OBBMaterial& obb) { // 分割軸の数
	std::vector<Vector3> separateAxes;
	separateAxes.resize(19);

	// 面の法線
	Vector3 normal[4];
	normal[0] = hexagon.normal[0];
	normal[1] = hexagon.normal[1];
	normal[2] = hexagon.normal[2];
	normal[3] = hexagon.normal[3];

	// 六角柱の面の法線
	separateAxes[0] = normal[0];
	separateAxes[1] = normal[1];
	separateAxes[2] = normal[2];
	separateAxes[3] = normal[3];
	// OBBの面の法線
	separateAxes[4] = obb.orientations[0];
	separateAxes[5] = obb.orientations[1];
	separateAxes[6] = obb.orientations[2];
	// クロス積で求める
	separateAxes[7] = Math::Cross(obb.orientations[0], normal[0]);
	separateAxes[8] = Math::Cross(obb.orientations[0], normal[1]);
	separateAxes[9] = Math::Cross(obb.orientations[0], normal[2]);
	separateAxes[10] = Math::Cross(obb.orientations[0], normal[3]);
	separateAxes[11] = Math::Cross(obb.orientations[1], normal[0]);
	separateAxes[12] = Math::Cross(obb.orientations[1], normal[1]);
	separateAxes[13] = Math::Cross(obb.orientations[1], normal[2]);
	separateAxes[14] = Math::Cross(obb.orientations[1], normal[3]);
	separateAxes[15] = Math::Cross(obb.orientations[2], normal[0]);
	separateAxes[16] = Math::Cross(obb.orientations[2], normal[1]);
	separateAxes[17] = Math::Cross(obb.orientations[2], normal[2]);
	separateAxes[18] = Math::Cross(obb.orientations[2], normal[3]);

	// 半分のベクトル
	/*obb*/
	Vector3 obbDirection[3]{
	    obb.orientations[0] * obb.size.x,
	    obb.orientations[1] * obb.size.y,
	    obb.orientations[2] * obb.size.z,
	};

	// 頂点の数
	const int kOBBCornerNum = 8;
	const int kHexagonCornerNum = 12;

	// 点(頂点)
	Vector3 obbCorners[kOBBCornerNum] = {
	    obb.center + obbDirection[0] + obbDirection[1] + obbDirection[2], // 背面の右上
	    obb.center + obbDirection[0] + obbDirection[1] - obbDirection[2], // 正面の右上
	    obb.center + obbDirection[0] - obbDirection[1] + obbDirection[2], // 背面の右下
	    obb.center + obbDirection[0] - obbDirection[1] - obbDirection[2], // 正面の右下
	    obb.center - obbDirection[0] + obbDirection[1] + obbDirection[2], // 背面の左上
	    obb.center - obbDirection[0] + obbDirection[1] - obbDirection[2], // 正面の左上
	    obb.center - obbDirection[0] - obbDirection[1] + obbDirection[2], // 背面の左下
	    obb.center - obbDirection[0] - obbDirection[1] - obbDirection[2], // 正面の左下
	};
	Vector3 hexagonConers[kHexagonCornerNum];

	// 半径と高さ
	Vector3 size = hexagon.size;

	// 六角形の頂点計算
	for (int i = 0; i < 6; i++) {
		float theta = 60.0f * static_cast<float>(i);
		float angle = radian(theta);
		float x = size.x * cos(angle);
		float z = size.z * sin(angle);

		// 上面の頂点 (z = +height)
		hexagonConers[i] = Math::Transform(Vector3(x, -size.y, z), Math::MakeRotateXYZMatrix(hexagon.rotation) * Math::MakeTranslateMatrix(hexagon.center));

		// 上面の頂点 (z = +height)
		hexagonConers[i + 6] = Math::Transform(Vector3(x, size.y, z), Math::MakeRotateXYZMatrix(hexagon.rotation) * Math::MakeTranslateMatrix(hexagon.center));
	}

	// 分離軸を増やす(六角形を回転させると高さが合わなくなるから)
	for (int i = 0; i < 6; i++) {
		int next = (i + 1) % 6;
		// 六角柱の辺
		Vector3 edgeTop = hexagonConers[next] - hexagonConers[i];
		Vector3 edgeBottom = hexagonConers[next + 6] - hexagonConers[i + 6];
		// OBB の辺
		Vector3 obbEdges[3] = {obbDirection[0], obbDirection[1], obbDirection[2]};

		// 辺同士のクロス積を分離軸に追加
		for (int j = 0; j < 3; j++) {
			Vector3 crossAxisTop = Math::Cross(edgeTop, obbEdges[j]);
			separateAxes.push_back(Math::Normalize(crossAxisTop));
			Vector3 crossAxisBottom = Math::Cross(edgeBottom, obbEdges[j]);
			separateAxes.push_back(Math::Normalize(crossAxisBottom));
		}
	}

	// 中心点間のベクトル
	Vector3 centerToCenter = hexagon.center - obb.center;

	// 当たったかの判定
	bool isHit = true;

	// 当たり判定の計算
	for (const auto& separateAxis : separateAxes) {
		float minOBB = (std::numeric_limits<float>::max)();
		float maxOBB = (std::numeric_limits<float>::lowest)();
		float minHexagon = minOBB;
		float maxHexagon = maxOBB;
		for (auto obbCornerIndex = 0; obbCornerIndex < kOBBCornerNum; obbCornerIndex++) {
			float obbDistance = Math::Dot(obbCorners[obbCornerIndex], separateAxis);
			minOBB = (std::min)(obbDistance, minOBB);
			maxOBB = (std::max)(obbDistance, maxOBB);
		}
		for (auto hexagonCornerIndex = 0; hexagonCornerIndex < kHexagonCornerNum; hexagonCornerIndex++) {
			float hexagonDistance = Math::Dot(hexagonConers[hexagonCornerIndex], separateAxis);
			minHexagon = (std::min)(hexagonDistance, minHexagon);
			maxHexagon = (std::max)(hexagonDistance, maxHexagon);
		}

		// それぞれを射影した範囲長の合計を求める
		float sumSpan = maxOBB - minOBB + maxHexagon - minHexagon;
		// 最大範囲を求める
		float longSpan = (std::max)(maxOBB, maxHexagon) - (std::min)(minOBB, minHexagon);
		if (sumSpan < longSpan) {
			isHit = false;
		}
	}

	return isHit;
}

// 球同士の衝突判定
bool operator==(const Shape::SphereMaterial& sphere1, const Shape::SphereMaterial& shpere2) { return Collision::GetInstance()->IsCollision(sphere1, shpere2); }

// AABB同士の衝突判定
bool operator==(const Shape::AABB& aabb1, const Shape::AABB& aabb2) { return Collision::GetInstance()->IsCollision(aabb1, aabb2); }

// OBB同士の衝突判定
bool operator==(const Shape::OBBMaterial& obb1, const Shape::OBBMaterial& obb2) { return Collision::GetInstance()->IsCollision(obb1, obb2); }

//OBBと六角柱の衝突判定
bool operator==(const Shape::OBBMaterial& obb, const Shape::HexagonMaterial& hexagon) { return Collision::GetInstance()->IsCollision(hexagon,obb); }
bool operator==(const Shape::HexagonMaterial& hexagon, const Shape::OBBMaterial& obb) { return Collision::GetInstance()->IsCollision(hexagon,obb); }
