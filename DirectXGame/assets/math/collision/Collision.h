#pragma once
#include "Vector3.h"
#include "Vector4.h"
//前方宣言
class WorldTransform;
class ViewProjection;

//AABB
typedef struct AABB {
	Vector3 min;
	Vector3 max;
} AABB;

/// <summary>
/// 衝突判定
/// </summary>
class Collision {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collision() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Collision() = default;

	/// <summary>
	///  球と球の衝突判定
	/// </summary>
	/// <param name="posA">座標A</param>
	/// <param name="posB">座標B</param>
	/// <param name="radiusA">半径A</param>
	/// <param name="radiusB">半径B</param>
	/// <returns></returns>
	static bool IsCollision(const Vector3& posA, const Vector3& posB, float radiusA, float radiusB);

	/// <summary>
	/// AABB
	/// </summary>
	/// <param name="aabb1">aabb1</param>
	/// <param name="aabb2">aabb2</param>
	/// <returns></returns>
	static bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// 線を表示
	/// </summary>
	/// <param name="worldPos">ワールドポジション</param>
	/// <param name="size">サイズ</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	static void DrawLine(Vector3 worldPos, Vector3 size, ViewProjection* viewProjection, Vector4 color = WHITE);

	/// <summary>
	/// 3Dの箱を作成
	/// </summary>
	/// <param name="worldPos">ワールドポジション</param>
	/// <param name="size">サイズ</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	static void DrawBox(Vector3 worldPos, Vector3 size, ViewProjection* viewProjection, Vector4 color = WHITE);
};
