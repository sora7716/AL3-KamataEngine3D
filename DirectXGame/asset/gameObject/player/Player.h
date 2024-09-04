#pragma once
#include "WorldTransform.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// プレイヤー
/// </summary>
class Player {


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() = default;

/// <summary>
	/// デストラクタ
/// </summary>
	~Player() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 親子関係作る
	/// </summary>
	void SetPearent(const WorldTransform* parent);

private://メンバ変数

	///モデル
	Model* model_ = nullptr;

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_;

};
