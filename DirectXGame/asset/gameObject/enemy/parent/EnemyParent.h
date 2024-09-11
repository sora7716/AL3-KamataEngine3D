#pragma once
#include "WorldTransform.h"

//前方宣言
class SkyDome;

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
	/// <param name="score_">スコア</param>
	void Update(int score_);

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

	/// <summary>
	/// ポジションのセッター
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(Vector3 position);

	/// <summary>
	/// スカイドームのセッター
	/// </summary>
	/// <param name="skyDome"></param>
	void SetSkyDome(SkyDome* skyDome);

private: // メンバ変数
	WorldTransform worldTransform_;//ワールドトランスフォーム
	SkyDome* skyDome_ = nullptr;//スカイドーム
};
