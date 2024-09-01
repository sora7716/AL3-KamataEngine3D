#pragma once
#include "WorldTransform.h"
#include "asset/math/collision/Collision.h"

// 前方宣言
class Model;
class ViewProjection;
class Player;

/// <summary>
/// 敵の弾
/// </summary>
class EnemyBullet {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBullet() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyBullet() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期の座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
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
	/// <returns></returns>
	bool IsDead() const;

	/// <summary>
	/// プレイヤーのセッター
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player*player);

	/// <summary>
	/// ワールドポジションのゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

private: // メンバ関数

	/// <summary>
	/// 追跡する弾
	/// </summary>
	void Tracking();

	/// <summary>
	/// 弾の向き
	/// </summary>
	void Direction();

public: // 静的メンバ変数

	static inline const int32_t kLifeTime = 60 * 10; // 寿命
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 1.0f;  // 横幅
	static inline const float kHeight = 1.0f; // 立幅
	static inline const float kDepth = 3.0f;  // 深さ

private: // メンバ変数

	Model* model_ = nullptr;         // モデル
	WorldTransform worldTransform_;  // ワールドトランスフォーム
	Vector3 velocity_ = {};          // 速度
	uint32_t texture_ = 0u;          // 弾のテクスチャハンドル
	int32_t deathTimer_ = kLifeTime; // デスタイマー
	bool isDead_ = false;            // デスフラグ
	Player* player_ = nullptr;       // プレイヤー
	float t = 0.0f;                  // 補間割合
	bool isTracking_ = true;//ホーミングしているかどうか
	int trackingTime_ = 0;//ホーミングし続ける時間
};
