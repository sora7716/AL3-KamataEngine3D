#pragma once
#include "WorldTransform.h"
#include "asset/math/Aithmetic.h"

// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// プレイヤーのバレットクラス
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
	/// デスフラグのゲッター
	/// </summary>
	/// <returns>isDead</returns>
	bool IsDead() const;

public:                                      // 静的メンバ変数
	static const int32_t kLifeTime = 60 * 5; // 寿命<frm>

private:                             // メンバ変数
	Model* model_ = nullptr;         // モデル
	WorldTransform worldTransform_;  // ワールドトランスフォーム
	uint32_t texture_ = 0u;          // テクスチャ
	Vector3 velocity_ = {};          // 速度
	int32_t deathTimer_ = kLifeTime; // デスタイマー
	bool isDead_ = false;            // デスフラグ
};
