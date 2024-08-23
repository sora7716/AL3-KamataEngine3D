#pragma once
#include "asset/gameObject/enemy/bullet/EnemyBullet.h"
#include <list>
using namespace std;

// 前方宣言
class WorldTransform;

/// <summary>
/// 敵のステートパターンのインターフェース
/// </summary>
class IEnemyState {

public: // 列挙型や構造体

	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
		phaseNum, // フェーズの数
	};

public: // メンバ関数

	// 純粋仮想関数
	IEnemyState() = default;
	virtual ~IEnemyState() = default;
	virtual void Initialize() = 0;
	virtual void ChangePhase() = 0;
	virtual void Exce(WorldTransform& worldTransform) = 0;
	virtual void Fire(WorldTransform& worldTransform) = 0;

public: // メンバ関数

	/// <summary>
	/// フェーズのゲッター
	/// </summary>
	/// <returns>現在のフェーズ</returns>
	int GetPhase() { return static_cast<int>(phase_); }

	/// <summary>
	/// 弾のゲッター
	/// </summary>
	/// <returns></returns>
	list<EnemyBullet*> GetBullet() { return bullets_; }

public: // 静的メンバ変数と関数ポインタ

	static inline const float kCharacterSpeed = 0.2f; // 敵の進むスピード

	static inline const int kPhaseNum = (int)Phase::phaseNum; // フェーズの数

	static void (IEnemyState::*EnemyPhaseTable[])(WorldTransform& worldTransform); // フェーズの関数ポインタ

	static inline const float kBulletSpeed = 1.0f; // 弾の速度

	static inline const int kFireInterval = 60; // 発射間隔

protected: // メンバ変数

	Phase phase_ = Phase::phaseNum; // フェーズ

	list<EnemyBullet*> bullets_ = {nullptr}; // 弾
	Model* bulletModel_ = nullptr;           // 弾のモデル
	int32_t fireTimer_ = 0;                  // 発射タイマー
};
