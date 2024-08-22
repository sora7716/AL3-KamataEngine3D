#pragma once
#include "asset/gameObject/enemy/statePattern/IEnemyState.h"

/// <summary>
/// 接近状態のフェーズ
/// </summary>
class EnemeyApproach : public IEnemyState {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemeyApproach() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemeyApproach() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 状態を遷移(接近状態から)
	/// </summary>
	void ChangePhase() override;

	/// <summary>
	/// 接近を実行
	/// </summary>
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Exce(WorldTransform& worldTransform);

	/// <summary>
	/// 攻撃
	/// </summary>
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Fire(WorldTransform& worldTransform) override;
};

/// <summary>
/// 離脱状態のフェーズ
/// </summary>
class EnemeyLeave : public IEnemyState {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemeyLeave() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemeyLeave() override = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 状態を遷移(離脱状態から)
	/// </summary>
	void ChangePhase() override;

	/// <summary>
	/// 離脱を実行
	/// </summary>
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Exce(WorldTransform& worldTransform);

	/// <summary>
	/// 攻撃
	/// </summary>
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Fire(WorldTransform& worldTransform) override;
};
