#pragma once
#include "WorldTransform.h"

//前方宣言(苦肉の策)
class ViewProjection;
class Model;

/// <summary>
/// 地面
/// </summary>
class Ground {

public:  // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ground() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ground() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialise(Model*model,ViewProjection*viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	Model* model_ = nullptr;//モデル
	ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション
	WorldTransform worldTransform_;//ワールドトランスフォーム
};
