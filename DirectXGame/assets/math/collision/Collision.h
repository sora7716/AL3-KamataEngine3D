#pragma once
#include "Vector3.h"
#include "Vector4.h"
// ワイヤーフレーム
#include "shape/Shape.h"
#include "shape/hexagon/Hexagon.h"
#include "shape/obb/OBB.h"
#include "shape/sphere/Sphere.h"
#include "shape/searchlight/Searchlight.h"
// 前方宣言
class WorldTransform;
class ViewProjection;

/// <summary>
/// 衝突判定
/// </summary>
class Collision final{
public: // メンバ関数

	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns>インスタンス</returns>
	static Collision* GetInstance();

	/// <summary>
	/// スフィアのインスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Sphere* GetSphereInstance();

	/// <summary>
	/// OBBのインスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static OBB* GetOBBInstance();

	/// <summary>
	/// 六角柱のインスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Hexagon* GetHexagonInstance();

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
	static bool IsCollision(const Shape::AABB& aabb1, const Shape::AABB& aabb2);

	//コピーコンストラクタを禁止
	Collision(const Collision& collision) = delete;
	//代入演算子を禁止
	const Collision operator=(const Collision& collision) = delete;

private: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collision() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Collision() = default;
};
