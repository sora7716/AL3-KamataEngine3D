#pragma once
#include "WorldTransform.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// タイトルフォント
/// </summary>
class TitleFont {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleFont()=default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleFont()=default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model*model,ViewProjection*viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	Model* model_ = nullptr;             // モデル
	ViewProjection* viewProjection_ = nullptr; // ビュープロジェクション
	WorldTransform worldTransform_;       // ワールドトランスフォーム
	float theta_ = 0.0f;
	float positionY = 0.0f;
};
