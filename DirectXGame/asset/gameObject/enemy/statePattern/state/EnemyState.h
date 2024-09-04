#pragma once
#include "asset/gameObject/enemy/statePattern/IEnemyState.h"

/// <summary>
/// 止まっているときのフェーズ
/// </summary>
class EnemyStay: public IEnemyState{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyStay() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyStay()override = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// フェーズを切り替え
	/// </summary>
	void ChangePhase() override;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="worldTransform"></param>
	void Exce(WorldTransform& worldTransform) override;
};

/// <summary>
/// 動いているときのフェーズ
/// </summary>
class EnemyMove : public IEnemyState {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyMove() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyMove() override = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// フェーズを切り替え
	/// </summary>
	void ChangePhase() override;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="worldTransform"></param>
	void Exce(WorldTransform& worldTransform) override;
};