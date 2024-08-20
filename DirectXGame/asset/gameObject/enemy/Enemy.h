#pragma once
#include "WorldTransform.h"
#include "asset/gameObject/enemy/statePattern/IEnemyState.h"
#include "asset/gameObject/enemy/statePattern/state/EnemyState.h"

// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// 敵のクラス
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
	/// <param name="texture">テクスチャハンドル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, ViewProjection* viewProjection, const uint32_t& texture, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	Model* model_ = nullptr;                                            // モデル
	ViewProjection* viewProjection_ = nullptr;                          // ビュープロジェクション
	WorldTransform worldTransform_;                                     // ワールドトランスフォーム
	uint32_t texture_ = 0u;                                             // テクスチャハンドル
	IEnemyState* action_[(int)IEnemyState::kPhaseNum] = {nullptr};               // 行動パターン
	int phase_ = 0;//現在の行動パターンの番号

};
