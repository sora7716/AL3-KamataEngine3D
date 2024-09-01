#pragma once
#include "WorldTransform.h"
#include "bullet/EnemyBullet.h"
#include "statePattern/IEnemyState.h"
#include "statePattern/state/EnemyState.h"
#include <list>
using namespace std;

// 前方宣言(苦肉の策)
class Model;
class ViewProjection;
class Player;
class GameScene;

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
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// タイトル用の初期化
	/// </summary>
	void TitleInitialize(Model* model, ViewProjection* viewProjection, const Vector3& position, const Vector3& angle);

	/// <summary>
	/// タイトル用の更新
	/// </summary>
	void TitleUpdate();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Fire();

	/// <summary>
	/// プレイヤーのセッター
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="phase">どの状態のとき</param>
	void SetPlayer(Player*player);

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

	/// <summary>
	/// ワールドポジションのゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォーム</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// ゲームシーンのセッター
	/// </summary>
	/// <param name="gameScene">ゲームシーン</param>
	void SetGameScene(GameScene* gameScene);

	/// <summary>
	/// 死亡フラグのゲッター
	/// </summary>
	bool IsDead()const;

public:  // 静的メンバ変数

	static inline const float kBulletSpeed = 1.0f; // 弾の速度
	static inline const int kFireInterval = 60; // 発射間隔
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 1.0f;  // 横幅
	static inline const float kHeight = 1.0f; // 立幅
	static inline const float kDepth = 1.0f;  // 深さ


private: // メンバ変数

	Model* model_ = nullptr;                                        // モデル
	ViewProjection* viewProjection_ = nullptr;                      // ビュープロジェクション
	WorldTransform worldTransform_;                                 // ワールドトランスフォーム
	IEnemyState* actions_[(int)IEnemyState::kPhaseNum] = {nullptr}; // 行動パターン
	int32_t phase_ = 2;                                             // 現在の行動パターンの番号
	int32_t fireTimer_ = 0;                                         // 発射タイマー
	Player* player_ = nullptr;                                      // プレイヤー
	GameScene* gameScene_ = nullptr;                                // ゲームシーン
	bool isDead_ = false;                                           // 死亡フラグ
};
