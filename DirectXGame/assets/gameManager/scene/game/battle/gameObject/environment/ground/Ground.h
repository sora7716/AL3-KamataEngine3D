#pragma once
#include "assets/gameManager/scene/game/battle/gameObject/environment/IEnvironment.h"

/// <summary>
/// 地面
/// </summary>
class Ground :public IEnvironment{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ground() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Ground() override = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection"></param>
	/// <param name="model"></param>
	void Initialize(Model* model,ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};
