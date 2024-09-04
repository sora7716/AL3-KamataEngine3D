#pragma once
#include "WorldTransform.h"

#pragma region 各クラスの前方宣言

class Model;         //モデル
class ViewProjection;//ビュープロジェクション

#pragma endregion 


/// <summary>
/// Playerクラスの宣言
/// </summary>
class Player {

public://メンバ関数

	///初期化処理
	void Initialize(Model* model, ViewProjection* viewProjection);

	///更新処理
	void Update();

	///描画処理
	void Draw();

private://メンバ変数

	///モデル
	Model* model_ = nullptr;

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_;

};
