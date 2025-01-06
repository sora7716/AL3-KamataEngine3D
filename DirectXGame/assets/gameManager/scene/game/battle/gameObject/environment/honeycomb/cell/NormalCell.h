#pragma once
#include "BaseCell.h"
class NormalCell :public BaseCell{
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NormalCell() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalCell() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 衝突したら
	/// </summary>
	/// <param name="isHit"></param>
	void OnCollision(bool isHit)override;
};
