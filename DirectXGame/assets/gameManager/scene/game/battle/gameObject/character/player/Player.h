#pragma once
#include "assets/gameManager/gameModel/create/playerModel/PlayerModel.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"

// 前方宣言
class ViewProjection;
class Model;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public BaseCharacter {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	Player() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection)override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// ビュープロジェクションのセッター
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetViewProjection(const ViewProjection* viewProjection);

	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	void GamepadControl();

	/// <summary>
	/// キーボードの操作
	/// </summary>
	void KeyboardControl();

private: // メンバ変数
	const ViewProjection* directionViewProjection_ = nullptr;
	// プレイヤーのモデル
	PlayerModel* playerModel_ = nullptr;

	Vector3 move_{};           // 移動量
	bool isMoving_ = false;    // 移動したかどうかのフラグ
	const float speed_ = 0.3f; // 速度
	float goalAngle_ = 0.0f;   // 目標角度
	float rotateFrame_ = 0.1f; // 回転するフレーム
};
