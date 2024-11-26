#pragma once
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"
#include "assets/gameManager/gameModel/create/mimicModel/MimicModel.h"
#include "Vector2.h"

/// <summary>
/// ミミックのクラス
/// </summary>
class Mimic :public BaseCharacter{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Mimic() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Mimic() = default;

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
	Vector3 circleMoveCenter_ = {5.0f,0.0f,10.0f};
	Vector2 circleMoveRadius_ = {10.0f, 5.0f};
};
