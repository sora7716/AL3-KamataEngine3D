#pragma once
#include "WorldTransform.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// ワープのクラス
/// </summary>
class Warp {
public://メンバ関数
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Warp() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Warp() = default;

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
	/// 親子関係を築づく
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform*parent);

private://メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	float size_ = 1.0f;
};