#pragma once
#include "assets/math/Math.h"
#include "assets/math/collision/Collision.h"


// 前方宣言
class ViewProjection;

class OBB {

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
	void Initialize(ViewProjection* viewProjection, const Math::OBBMaterial&& obbMaterial);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="type">名前</param>
	void DebagText(const char* type = "obb");

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
	Math::OBBMaterial GetOBBMaterial() const;

	/// <summary>
	/// 衝突したら
	/// </summary>
	void OnCollision(bool isHit);

private: // メンバ関数
	/// <summary>
	/// 頂点を作成
	/// </summary>
	void MakeVertecies();

private:                                                    // メンバ変数
	Math::OBBMaterial obb_ = {};                            // obb
	Matrix4x4 invers_ = {};                                 // obbの逆行列
	ViewProjection* viewProjection_ = nullptr;              // ビュープロジェクション
	AABB aabb_ = {};                                        // AABBのマテリアル
	Math::Vertex2D localVertecies_[Math::kAABB2DNum] = {};  // ローカルの頂点
	Math::Vertex2D screenVertecies_[Math::kAABB2DNum] = {}; // スクリーンの頂点
	Matrix4x4 worldViewProjection_ = {};                    // ワールドビュープロジェクション
	Vector3 rotate_ = {};                                   // 回転ベクトル
	Matrix4x4 worldMatrix_ = {};                            // ワールド行列
	Matrix4x4 viewport_ = {};                               // ビューポート
};
