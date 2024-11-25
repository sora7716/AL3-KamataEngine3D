#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

class IEnvironment {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	IEnvironment() = default;

	// 純粋仮想関数
	virtual ~IEnvironment() = default;
	virtual void Initialize(Model* model,ViewProjection* viewprojection) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected: // メンバ変数
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
};