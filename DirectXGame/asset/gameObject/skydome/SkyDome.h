#pragma once
#include "WorldTransform.h"
#include "numbers"

class Model;
class ViewProjection;

class SkyDome {

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model *model,ViewProjection *viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	Vector3 GetWorldTransform()const;

private:

	//モデル
	Model* model_ = nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;

};
