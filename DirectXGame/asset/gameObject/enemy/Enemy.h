#pragma once
#include "WorldTransform.h"
#include "bullet/EnemyBullet.h"
#include "statePattern/IEnemyState.h"
#include "statePattern/state/EnemyState.h"
#include <list>
using namespace std;

// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// 敵
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

	Model* model_ = nullptr;                                       // モデル
	ViewProjection* viewProjection_ = nullptr;                     // ビュープロジェクション
	WorldTransform worldTransform_;                                // ワールドトランスフォーム
	uint32_t texture_ = 0u;                                        // テクスチャハンドル
	IEnemyState* actions_[(int)IEnemyState::kPhaseNum] = {nullptr}; // 行動パターン
	int32_t phase_ = 0;                                            // 現在の行動パターンの番号
	int32_t prePhase_ = phase_;                                     // 前の行動パターンの番号
};
