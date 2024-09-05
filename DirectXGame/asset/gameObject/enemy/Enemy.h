#pragma once
#include "WorldTransform.h"
#include "asset/gameObject/enemy/statePattern/state/EnemyState.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// 障害物
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
	/// <param name="position">初期位置</param>
	void Initialize(Model* model, ViewProjection* viewProjection, Vector3 position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
#pragma region ステートパターン

	/// <summary>
	/// 止まっているとき
	/// </summary>
	void StatusStay();

	/// <summary>
	/// 横移動しているとき
	/// </summary>
	void StatusLateralMove();
#pragma endregion

	/// <summary>
	/// ステータスが変わったかどうか
	/// </summary>
	/// <returns>ステータスが変わったかどうかのフラグ</returns>
	bool IsStatusChange();

	/// <summary>
	/// ステータスが変わったかどうかのセッター
	/// </summary>
	/// <param name="isStatusChange">ステータスのフラグに設定したい値</param>
	void SetIsStatusChange(bool isStatusChange);

private: // メンバ変数
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	//初期位置
	Vector3 firstPos = {};
	// 障害物の状態
	IEnemyState*actions_[IEnemyState::kStatusNum];
	//ステータス
	int status_ = IEnemyState::kStatusNum;
	//ステータスをチェンジ
	bool isStatusChange_ = false;
};
