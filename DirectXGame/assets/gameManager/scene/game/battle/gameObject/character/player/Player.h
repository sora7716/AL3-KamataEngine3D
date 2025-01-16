#pragma once
#include "assets/gameManager/gameModel/create/playerModel/PlayerModel.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"
#include "assets/gameManager/scene/game/battle/gameObject/ui/LifeBar/LifeBar.h"
#include "assets/gameManager/scene/game/battle/gameObject/ui/MpBar/MpBar.h"

// 前方宣言
class ViewProjection;
class Model;
//class LifeBar;
class Create;

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
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection, const std::vector<uint32_t>&& textures) override;

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
	/// ゲームパッドの操作
	/// </summary>
	void GamepadControl();

	/// <summary>
	/// キーボードの操作
	/// </summary>
	void KeyboardControl();

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
	/// <summary>
	/// キャラクタータイプのゲッター
	/// </summary>
	/// <returns></returns>
	int GetCharacterType() { return (int)charType_; }

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	/// <param name="partsName"></param>
	/// <returns></returns>
	AABB GetPartsAABB(PlayerModel::Parts partsName);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	PlayerMode GetBehavior();

	/// <summary>
	/// ダメージを受けた
	/// </summary>
	void TookDamage() { playerLifeBar_->TookDamage(); }

	/// <summary>
	/// 死亡ゲッター
	/// </summary>
	/// <returns>死亡か否か</returns>
	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// 死亡セッター
	/// </summary>
	/// <param name="input"></param>
	void SetIsDead(bool input) { isDead_ = input; }

	/// <summary>
	/// 2D描画
	/// </summary>
	void DrawSprite(){ playerLifeBar_->Draw(); }
private://メンバ関数

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

public:                                                  // 静的メンバ変数
	static inline const uint32_t kBehaviorDashTime = 60; // ダッシュの時間の上限
	static inline const int kBlowTime =90;              // 打撃の継続時間
	static inline float const kSpeed_ = 0.3f;            // 速度
	static void (Player::*ActionTable[])();//アクションテーブル

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
	//ライフバー
	std::unique_ptr<LifeBar> playerLifeBar_ = nullptr;
	//MPバー
	std::unique_ptr<MpBar> playerMpBar_ = nullptr;
	//死亡管理
	bool isDead_ = false;
	// ジョイスティックの状態
	XINPUT_STATE joyState_, preJoyState_; // 現在と過去
};
