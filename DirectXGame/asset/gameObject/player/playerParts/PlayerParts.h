#pragma once
#include "IPlayerParts.h"

class PlayerHead : public IPlayerParts {

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

class PlayerBody : public IPlayerParts {

public:
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};

class PlayerLeft_Arm : public IPlayerParts {

public:
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};

class PlayerRight_Arm : public IPlayerParts {

public:
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};