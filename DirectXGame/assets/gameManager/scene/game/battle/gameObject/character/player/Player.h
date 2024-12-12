#pragma once
#include "assets/gameManager/gameModel/create/playerModel/PlayerModel.h"
#include "assets/gameManager/scene/game/baseGameObject/baseCharacter/basePlayer/BasePlayer.h"

// 前方宣言
class ViewProjection;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public BasePlayer {
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
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ビュープロジェクションのセッター
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetViewProjection(const ViewProjection* viewProjection);

	/// <summary>
	/// playerのposゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() { return worldTransform_.translation_; }

	/// <summary>
	/// ダッシュの初期化
	/// </summary>
	void BehaviorDashInitialize();

	/// <summary>
	// ダッシュの更新
	/// </summary>
	void BehaviorDashUpdate();

private: // メンバ関数
	/// <summary>
	/// 通常行動用
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 打撃用
	/// </summary>
	void BehaviorBlowUpdate();

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="speed">速度</param>
	void Moving(float speed);

public: // コマンド
	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	void GamepadControl();

#pragma region キーボード
	/// <summary>
	/// キーボードの操作
	/// </summary>
	void KeyboardControl();

	/// <summary>
	/// 左に進む
	/// </summary>
	void MoveLeftKeyboard();

	/// <summary>
	/// 右に進む
	/// </summary>
	void MoveRightKeyboard();

	/// <summary>
	/// 前に進む
	/// </summary>
	void MoveFrontKeyboard();

	/// <summary>
	/// 後ろに進む
	/// </summary>
	void MoveBackKeyboard();
#pragma endregion
	
	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="axis">軸</param>
	void Reset(float axis);

public:                                                  // 静的メンバ変数
	static inline const uint32_t kBehaviorDashTime = 60; // ダッシュの時間の上限
	static inline const int kBlowTime = 90;              // 打撃の継続時間
	static inline float const kSpeed_ = 0.3f;            // 速度
	static void (Player::*ActionTable[])();              // アクションテーブル

private: // メンバ変数
	const ViewProjection* directionViewProjection_ = nullptr;
	// プレイヤーのモデル
	std::unique_ptr<PlayerModel> playerModel_ = nullptr; // プレイヤーの体
	Vector3 move_{};                                     // 移動量
	bool isMoving_ = false;                              // 移動したかどうかのフラグ
	float goalAngle_ = 0.0f;                             // 目標角度
	float rotateFrame_ = 0.5f;                           // 回転するフレーム
	bool isBlow_ = false;                                // 打撃を開始
	float blowBeginPos_ = 0.0f;                          // 打撃を開始した位置
	float speed_ = kSpeed_;                              // スピード
	float speedScaler_ = 10.0f;                          // スピードの倍率
	// ジョイスティックの状態
	XINPUT_STATE joyState_, preJoyState_; // 現在と過去
};
