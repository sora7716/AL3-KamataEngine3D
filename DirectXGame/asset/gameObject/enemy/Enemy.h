#pragma once
#include "WorldTransform.h"
#include "bullet/EnemyBullet.h"
#include "statePattern/IEnemyState.h"
#include "statePattern/state/EnemyState.h"
#include "asset/gameObject/enemy/bullet/EnemyBullet.h"
#include "asset/math/TimedCall.h"
#include <list>
using namespace std;

// 前方宣言
class Model;
class ViewProjection;
class Player;

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

	/// <summary>
	/// 攻撃
	/// </summary>
	void Fire();

	/// <summary>
	/// 弾を発射し、タイマーをリセットするコールバック関数
	/// </summary>
	void FireTimeReset();

	/// <summary>
	/// プレイヤーのセッター
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="phase">どの状態のとき</param>
	void SetPlayer(Player*player);

	/// <summary>
	/// ワールドポジションのゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetWorldPosition();

public:  // 静的メンバ変数

	static inline const float kBulletSpeed = 1.0f; // 弾の速度
	static inline const int kFireInterval = 60; // 発射間隔

private: // メンバ変数

	Model* model_ = nullptr;                                        // モデル
	ViewProjection* viewProjection_ = nullptr;                      // ビュープロジェクション
	WorldTransform worldTransform_;                                 // ワールドトランスフォーム
	uint32_t texture_ = 0u;                                         // テクスチャハンドル
	IEnemyState* actions_[(int)IEnemyState::kPhaseNum] = {nullptr}; // 行動パターン
	int32_t phase_ = 0;                                             // 現在の行動パターンの番号
	list<EnemyBullet*> bullets_;                                    // 弾
	Model* bulletModel_ = nullptr;                                  // 弾のモデル
	int32_t fireTimer_ = 0;                                         // 発射タイマー
	Player* player_ = nullptr;                                      // プレイヤー
	list<TimedCall*> timedCalls_;                                   // 時限発動リスト
	bool isTimeReset_ = false;                                      // 時限発動のフラグ
};
