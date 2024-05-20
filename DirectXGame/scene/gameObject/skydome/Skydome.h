#pragma once
#include "Model.h"
#include "WorldTransform.h"
/// <summary>
/// 天球
/// </summary>
class Skydome {

public://メンバ関数

	/// <summary>
	/// スカイドームの初期化処理
	/// </summary>
	/// <param name="model">3Dモデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// スカイドームの更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// スカイドームの描画処理
	/// </summary>
	void Draw();

private://メンバ変数

	
	WorldTransform worldTransform_;//ワールド変換データ
	
	Model* model_ = nullptr;//モデル
	
	ViewProjection* viewProjection_;//ビュープロジェクション

};