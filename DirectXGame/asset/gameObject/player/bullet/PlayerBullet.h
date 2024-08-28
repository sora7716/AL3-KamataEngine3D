#pragma once
#include "WorldTransform.h"
#include "asset/math/Aithmetic.h"
#include"asset/math/collision/Collision.h"

// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// プレイヤーのバレット
/// </summary>
class PlayerBullet {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// デスフラグのゲッター
	/// </summary>
	/// <returns>isDead</returns>
	bool IsDead() const;

	/// <summary>
	/// ワールドポジションのゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

public: // 静的メンバ変数

	static const int32_t kLifeTime = 60 * 5; // 寿命<frm>
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 1.0f;  // 横幅
	static inline const float kHeight = 1.0f; // 立幅
	static inline const float kDepth = 1.0f;  // 深さ

private:                             // メンバ変数
	Model* model_ = nullptr;         // モデル
	WorldTransform worldTransform_;  // ワールドトランスフォーム
	uint32_t texture_ = 0u;          // テクスチャ
	Vector3 velocity_ = {};          // 速度
	int32_t deathTimer_ = kLifeTime; // デスタイマー
	bool isDead_ = false;            // デスフラグ
};
