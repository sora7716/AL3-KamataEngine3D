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

	/// <summary>
	/// ビュープロジェクションのセッター
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetViewProjection(const ViewProjection* viewProjection);

private://メンバ変数
	PlayerModel* playerModel_ = nullptr;
	const ViewProjection* directionViewProjection_ = nullptr;
	Vector3 move_{};           // 移動量
	bool isMoving_ = false;    // 移動したかどうかのフラグ
	const float speed_ = 0.3f; // 速度
	float goalAngle_ = 0.0f;   // 目標角度
	float rotateFrame_ = 0.5f; // 回転するフレーム
};
