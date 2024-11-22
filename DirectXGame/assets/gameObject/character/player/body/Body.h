#pragma once
#include "WorldTransform.h"
// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// プレイヤーの体のインターフェース
/// </summary>
class IBody {
public: // メンバ関数
	IBody() = default;
	//純粋仮想関数
	virtual ~IBody() = default;
	virtual void Initialize(Model* model, ViewProjection* viewProjection) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

private://メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection;
};

//class 
