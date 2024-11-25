#pragma once
#include "WorldTransform.h"
#include "playerModel/PlayerModel.h"
#include <memory>
#include <vector>

// 前方宣言
class ViewProjection;
class Model;

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public: // メンバ関数
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
	/// <param name="model">モデル</param>
	void Initialize(std::vector<std::unique_ptr<Model>>&& model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform();

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
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
	const ViewProjection* directionViewProjection_ = nullptr;
	PlayerModel* playerModel_ = nullptr;

	Vector3 move_{};           // 移動量
	bool isMoving_ = false;    // 移動したかどうかのフラグ
	const float speed_ = 0.3f; // 速度
	float goalAngle_ = 0.0f;   // 目標角度
	float rotateFrame_ = 0.1f; // 回転するフレーム
};
