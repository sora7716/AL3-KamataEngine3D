#pragma once

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
		phaseNum, //フェーズの数
	};

public: // メンバ関数

	// 純粋仮想関数
	IEnemyState() = default;
	virtual ~IEnemyState() = default;
	virtual void ChangePhase() = 0;
	virtual void Exce(WorldTransform& worldTransform) = 0;

public://メンバ関数

	/// <summary>
	/// フェーズのゲッター
	/// </summary>
	/// <returns>現在のフェーズ</returns>
	int GetPhase() { return static_cast<int>(phase_); }

public:// 静的メンバ変数

	static inline const float kCharacterSpeed = 0.2f; // 敵の進むスピード

	static inline const int kPhaseNum = (int)Phase::phaseNum;//フェーズの数


protected: // メンバ変数

	Phase phase_ = Phase::Approach; // フェーズ
};
