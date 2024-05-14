#pragma once
#include "Model.h"
#include "WorldTransform.h"
/// <summary>
/// 天球
/// </summary>
class Skydome {

public://メンバ関数

	void Initialize();

	void Update();

	void Draw();

private://メンバ変数

	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model = nullptr;

};