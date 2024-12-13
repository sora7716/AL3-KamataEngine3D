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
	/// 球同士の当たり判定
	/// </summary>
	/// <param name="sphere1">球1</param>
	/// <param name="sphere2">球2</param>
	/// <returns></returns>
	static bool IsCollision(const Shape::SphereMaterial& sphere1, const Shape::SphereMaterial& sphere2);

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

//球同士の当たり判定
bool operator==(const Shape::SphereMaterial& sphere1, const Shape::SphereMaterial& shpere2);

//AABB同士の当たり判定
bool operator==(const Shape::AABB& aabb1, const Shape::AABB& aabb2);