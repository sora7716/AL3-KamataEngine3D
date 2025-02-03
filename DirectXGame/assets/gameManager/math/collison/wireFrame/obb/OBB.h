#pragma once
#include "assets/gameManager/math/collison/wireFrame/Shape.h"
// 前方宣言
class ViewProjection;

class OBB : public Shape {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	OBB() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OBB() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="obbMaterial">obbの素材</param>
	void Initialize(const OBBMaterial&& obbMaterial,ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="type">名前</param>
	void DebagText(const char* label = "obb");

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールドマトリックス逆行列のゲッター
	/// </summary>
	/// <returns>ワールドマトリックス逆行列</returns>
	Matrix4x4 GetOBBWorldMatrixInvers() const;

	/// <summary>
	/// サイズのゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetSize() const;

	/// <summary>
	/// OBBのマテリアルのゲッター
	/// </summary>
	/// <returns></returns>
	OBBMaterial GetOBBMaterial() const;

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	/// <returns></returns>
	AABB GetAABB();

	/// <summary>
	/// スケールのセッター
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(const Vector3 scale)override;

	/// <summary>
	/// 回転のセッター
	/// </summary>
	/// <param name="rotate">回転</param>
	void SetRotate(const Vector3 rotate)override;

	/// <summary>
	/// 現在地のセッター
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const Vector3 position)override;

private: // メンバ関数
	/// <summary>
	/// 頂点を作成
	/// </summary>
	void MakeVertecies();

private:                                              // メンバ変数
	OBBMaterial obb_ = {};                            // obb
	Matrix4x4 invers_ = {};                           // obbの逆行列
	AABB aabb_ = {};                                  // AABBのマテリアル
	Vertex2D localVertecies_[Math::kAABB2DNum] = {};  // ローカルの頂点
	Vertex2D screenVertecies_[Math::kAABB2DNum] = {}; // スクリーンの頂点
	Matrix4x4 worldViewProjection_ = {};              // ワールドビュープロジェクション
};
