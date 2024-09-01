#pragma once
#include "WorldTransform.h"
#include <cmath>
#define _USE_MATH_DEFINES

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// ゲームのスタートボタン
/// </summary>
class GameStart {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameStart()=default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStart()=default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="texture">テクスチャハンドル</param>
	void Initiaize(Model* model, ViewProjection* viewProjection, uint32_t texture);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private://メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	uint32_t texture_ = 0u;
	WorldTransform worldTransform_;
};
