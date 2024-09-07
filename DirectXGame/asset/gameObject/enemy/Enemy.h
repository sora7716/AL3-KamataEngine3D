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
	void Initialize(Model* model, ViewProjection* viewProjection, Vector3 position);

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
#pragma endregion

	/// <summary>
	/// ステータスが変わったかどうか
	/// </summary>
	/// <returns>ステータスが変わったかどうかのフラグ</returns>
	bool IsStatusChange();

	/// <summary>
	/// ステータスが変わったかどうかのセッター
	/// </summary>
	/// <param name="isStatusChange">ステータスのフラグに設定したい値</param>
	void SetIsStatusChange(bool isStatusChange);

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

	void SetPosition(Vector3 position);

public: // 静的メンバ変数

	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 1.0f;  // 横幅
	static inline const float kHeight = 1.0f; // 立幅
	static inline const float kDepth = 1.0f;  // 深さ

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
	//ステータスをチェンジ
	bool isStatusChange_ = false;
	bool isDead_ = false;
};
