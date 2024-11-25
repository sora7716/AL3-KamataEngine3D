#pragma once
#include "assets/gameManager/scene/game/battle/gameObject/environment/IEnvironment.h"

/// <summary>
/// 天球
/// </summary>
class Skydome : public IEnvironment {
public: // メンバ関数
	/// <summary>
	/// コントラクタ
	/// </summary>
	Skydome() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Skydome() override = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;


};
