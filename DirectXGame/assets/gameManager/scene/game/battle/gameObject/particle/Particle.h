#pragma once
#include "WorldTransform.h"
#include "ObjectColor.h"

//前方宣言
class Model;
class ViewProjection;

/// <summary>
/// パーティクル
/// </summary>
class Particle {
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Particle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Particle() = default;

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
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	ObjectColor objectColor_ = {};
	Vector4 color_ = RED;
};
