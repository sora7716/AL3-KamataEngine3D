#pragma once
#include <Vector3.h>
#include <cmath>
#define _USE_MATH_DEFINES

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

public: // メンバ関数

	/// <summary>
	/// フェーズのゲッター
	/// </summary>
	/// <returns>現在のフェーズ</returns>
	int GetPhase() { return static_cast<int>(phase_); }

	/// <summary>
	/// フェーズのセッター
	/// </summary>
	/// <param name="phase"></param>
	void SetPhase(uint32_t phase) { phase_ = static_cast<Phase>(phase); };

	/// <summary>
	/// 最初の位置のセッター
	/// </summary>
	/// <param name="position">最初の位置</param>
	void SetFirstPosition(Vector3 position) { firstPosition_ = position; };


public: // 静的メンバ変数と関数ポインタ

	static inline const float kCharacterSpeed = 0.2f; // 敵の進むスピード

	static inline const int kPhaseNum = (int)Phase::phaseNum; // フェーズの数

	static void (IEnemyState::*EnemyPhaseTable[])(WorldTransform& worldTransform); // フェーズの関数ポインタ

protected: // メンバ変数
	Phase phase_ = Phase::phaseNum; // フェーズ
	Vector3 firstPosition_ = {};
};
