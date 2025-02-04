#pragma once
#include "assets/gameManager/scene/game/gameObject/character/BaseCharacter.h"

//前方宣言
class PlayerModel;

/// <summary>
/// プレイヤー
/// </summary>
class Player :public BaseCharacter{
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="models">モデル</param>
	void Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models)override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// プレイヤーモデルのセッター
	/// </summary>
	/// <param name="playerModel"></param>
	void SetPlayerModel(std::shared_ptr<PlayerModel>&& playerModel);

private://メンバ変数
	PlayerModel* playerModel_ = nullptr;
};
