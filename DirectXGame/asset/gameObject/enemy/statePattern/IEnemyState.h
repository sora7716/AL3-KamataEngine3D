#pragma once
#include <cmath>
#define _USE_MATH_DEFINES

//前方宣言(苦肉の策)
class Enemy;

/// <summary>
/// 障害物の状態のインターフェース
/// </summary>
class IEnemyState {
public://列挙型
	enum class Status {
		kStay,//止まっている
		kMove,//動く
		phaseEmpty,//フェーズが何も入っていない
	};

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEnemyState() = default;

	/// <summary>
	/// ステータスのゲッター
	/// </summary>
	/// <returns>ステータス</returns>
	int GetStatus() { return static_cast<int>(status_); }

	/// <summary>
	/// ステータスのセッター
	/// </summary>
	/// <param name="status">セットしたいステータス</param>
	void SetStatus(int status) { status_ = static_cast<Status>(status); }
	
	/// <summary>
	/// 純粋関数の初期化
	/// </summary>
	virtual void Initialize() = 0;

protected: // メンバ関数
	//純粋仮想関数
	virtual ~IEnemyState() = default;
	virtual void ChangePhase() = 0;
	virtual void Exce(Enemy& enemy) = 0;

public: // 静的メンバ変数
	static inline const int kStatusNum = (int)Status::phaseEmpty;//フェーズの数
	static void (IEnemyState::*EnemyPhaseTable[])(Enemy& enemy);  // フェーズを実行する関数ポインタ

protected: // メンバ変数
	Status status_ = Status::phaseEmpty; // 障害物の状態

};