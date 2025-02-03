#pragma once
#include "assets/gameManager/gameModel/create/playerModel/PlayerModel.h"

class StaffModel : public IPlayerModel {
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StaffModel() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StaffModel() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};
