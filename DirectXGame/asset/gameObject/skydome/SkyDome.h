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
	/// <param name="isMove">スカイドームが動くかのフラグ</param>
	void Update(bool isMove = true);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	Vector3 GetWorldTransform()const;

	/// <summary>
	/// トランスレイションのセッター
	/// </summary>
	/// <param name="position">セットしたい位置</param>
	void SetTranslation(const Vector3& position);

private:

	//モデル
	Model* model_ = nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;

};
