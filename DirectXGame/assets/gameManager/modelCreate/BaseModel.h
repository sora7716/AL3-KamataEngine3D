#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ベースモデル
/// </summary>
class BaseModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseModel() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseModel() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	virtual void Initialize(ViewProjection* viewProjection, Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 親のセッター
	/// </summary>
	/// <param name="parent"></param>
	virtual void SetParent(const WorldTransform* parent);

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	virtual const WorldTransform* GetWorldTransform();

protected: // メンバ変数
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
};
