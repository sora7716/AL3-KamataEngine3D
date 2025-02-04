#pragma once
#include "assets/gameManager/scene/game/gameObject/environment/BaseEnvironment.h"
/// <summary>
/// 天球
/// </summary>
class Skydome : public BaseEnvironment{
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
	void Initialize(ViewProjection* viewProjection, std::shared_ptr<Model>&& model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;


};
