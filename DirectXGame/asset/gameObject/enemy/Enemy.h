#pragma once
#include "WorldTransform.h"
#include "asset/gameObject/enemy/statePattern/state/EnemyState.h"
#include "asset/math/collision/Collision.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// 障害物
/// </summary>
class Enemy {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="position">初期位置</param>
	void Initialize(Model* model, ViewProjection* viewProjection, Vector3 position = {});

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突したとき
	/// </summary>
	void OnCollision();

#pragma region ステートパターン

	/// <summary>
	/// 止まっているとき
	/// </summary>
	void StatusStay();

	/// <summary>
	/// 横移動しているとき
	/// </summary>
	void StatusLateralMove();

	/// <summary>
	/// 縦移動
	/// </summary>
	void StatusVerticalMove();
#pragma endregion

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

	/// <summary>
	/// 座標のセッター
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(Vector3 position);

	/// <summary>
	/// 親のセッター
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// 敵の状態のセッター
	/// </summary>
	/// <param name="score"></param>
	void SetStatus(int score);

public: // 静的メンバ変数

	static inline const float kRot = 10.0f;//回転する速さ
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 2.0f;  // 横幅
	static inline const float kHeight = 2.0f; // 立幅
	static inline const float kDepth = 2.0f;  // 深さ

private: // メンバ変数
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	//初期位置
	Vector3 firstPos = {};
	// 障害物の状態
	IEnemyState*actions_[IEnemyState::kStatusNum];
	//ステータス
	int status_ = IEnemyState::kStatusNum;
	//敵の状態
	int randomNum_ = 0;
};
