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
	
	/// <summary>
	/// 通常状態の初期化
	/// </summary>
	void BehaviorRootReset()override;

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate() override;

	/// <summary>
	/// 打撃
	/// </summary>
	void BehaviorBlowUpdate() override;

	/// <summary>
	/// ダッシュ時の更新
	/// </summary>
	void BehaviorDashUpdate() override;
};
