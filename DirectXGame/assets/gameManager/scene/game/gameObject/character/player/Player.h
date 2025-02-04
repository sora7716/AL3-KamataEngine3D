#pragma once
#include "assets/gameManager/scene/game/gameObject/character/BaseCharacter.h"

// 前方宣言
class PlayerModel;
class Camera;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public BaseCharacter {
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
	/// <param name="models">モデル</param>
	void Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

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
	/// カメラのセッター
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(Camera* camera);

private: // メンバ関数
	/// <summary>
	/// ゲームパッドで操作
	/// </summary>
	void GamepadControl();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

public:// 静的メンバ変数
	static inline const float kRotSpeed_ = -5.0f; // カメラの回転スピード

private: // メンバ変数
	PlayerModel* playerModel_ = nullptr;
	Vector3 move_{};           // 移動量
	bool isMoving_ = false;    // 移動したかどうかのフラグ
	const float speed_ = 0.3f; // 速度
	float goalAngle_ = 0.0f;   // 目標角度
	float rotateFrame_ = 0.3f; // 回転するフレーム
	Camera* camera_ = nullptr; // カメラ
};
