#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>
#include <cassert>

/// <summary>
/// 環境のベース
/// </summary>
class BaseEnvironment {
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseEnvironment() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseEnvironment() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	virtual void Initialize(ViewProjection* viewProjection, std::shared_ptr<Model> model);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
protected: // メンバ変数
	std::shared_ptr<Model> model_;
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
};
