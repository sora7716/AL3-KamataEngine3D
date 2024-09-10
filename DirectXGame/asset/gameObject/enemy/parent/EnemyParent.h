#pragma once
#include "WorldTransform.h"
/// <summary>
/// 障害物の親クラス
/// </summary>
class EnemyParent {

public:  // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyParent() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyParent() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 親クラスのセット
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	WorldTransform& GetWorldTransform();

private: // メンバ変数
	WorldTransform worldTransform_;//ワールドトランスフォーム
};
