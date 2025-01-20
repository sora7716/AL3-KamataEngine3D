#pragma once
#include "assets/gameManager/gameModel/create/playerModel/PlayerModel.h"
#include "assets/gameManager/scene/game/baseGameObject/baseCharacter/BaseCharacter.h"
#include "inputHandle/InputHandle.h"
#include "assets/gameManager/scene/game/battle/gameObject/ui/lifebar/LifeBar.h"
#include "assets/gameManager/scene/game/battle/gameObject/ui/mpbar/MpBar.h"

// 前方宣言
class ViewProjection;

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
	~Player();

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
	/// 2D描画
	/// </summary>
	void DrawSprite();

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
	/// ワイヤーフレームのゲッター
	/// </summary>
	/// <returns></returns>
	OBB* GetWireFrame();

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
	/// 横移動していないとき
	/// </summary>
	void StopHorizontal();

	/// <summary>
	/// 前に進む
	/// </summary>
	void MoveFrontKeyboard();

	/// <summary>
	/// 後ろに進む
	/// </summary>
	void MoveBackKeyboard();

	/// <summary>
	/// 垂直移動を止める
	/// </summary>
	void StopVertical();

	/// <summary>
	/// キーの生成
	/// </summary>
	void CreateInputKey();
#pragma endregion

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
	bool isHorizontalMove_ = false;                      // 水平移動したかどうかのフラグ
	bool isVerticalMove_ = false;                        // 垂直移動したかどうかのフラグ
	float goalAngle_ = 0.0f;                             // 目標角度
	float rotateFrame_ = 0.3f;                           // 回転するフレーム
	bool isBlow_ = false;                                // 打撃を開始
	float blowBeginPos_ = 0.0f;                          // 打撃を開始した位置
	float speed_ = kSpeed_;                              // スピード
	float speedScaler_ = 0.0f;                          // スピードの倍率
	// ジョイスティックの状態
	XINPUT_STATE joyState_, preJoyState_; // 現在と過去
	// キーボードの操作
	std::unique_ptr<InputHandle> inputHandle_ = nullptr; // インプットハンドル
	ICommand* horizontalCommand_ = nullptr;              // 水平移動
	ICommand* verticalCommand_ = nullptr;                // 垂直移動
	
	//ライフバー
	std::unique_ptr<LifeBar> playerLifeBar_ = nullptr;
	//MPバー
	std::unique_ptr<MpBar> playerMpBar_ = nullptr;
	//死亡管理
	bool isDead_ = false;
};
