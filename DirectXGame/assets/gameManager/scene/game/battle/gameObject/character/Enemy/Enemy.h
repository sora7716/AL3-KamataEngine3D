#pragma once
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"
#include "assets/gameManager/gameModel/create/mimicModel/MimicModel.h"
class Enemy :public BaseCharacter{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private://メンバ変数
	MimicModel* mimicModel_ = nullptr;
};
