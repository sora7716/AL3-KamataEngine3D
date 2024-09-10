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
	void Exce(Enemy&enemy) override;
};

/// <summary>
/// 横に動いているときのフェーズ
/// </summary>
class EnemyLateralMove : public IEnemyState {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyLateralMove() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyLateralMove() override = default;

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
	void Exce(Enemy& enemy) override;
};

/// <summary>
/// 縦に動いているときのフェーズ
/// </summary>
class EnemyVerticalMove : public IEnemyState {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyVerticalMove() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyVerticalMove() override = default;

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
	void Exce(Enemy& enemy) override;
};