#pragma once
#include "assets/gameobject/BaseCharacter.h"

#include "assets/math/Math.h"
#include "memory"
#include "vector"
#include <optional>

// 各クラスの前方宣言
class Input;
class LockOn;
class Hammer;

/// <summary>
/// 自キャラ
/// </summary>
class Player : public BaseCharacter, Math {

public:
	// プレイヤーパーツの列挙体
	enum class Parts {
	    kBase,
	    kBody,
    	kHead,
	    kLeft_arm,
	    kRight_arm,
	    kPartNum
    };

	using ObjectParts = Parts;
	static inline ObjectParts typeBase = Parts::kBase;
	static inline ObjectParts typeBody = Parts::kBody;
	static inline ObjectParts typeHead = Parts::kHead;
	static inline ObjectParts typeL_arm = Parts::kLeft_arm;
	static inline ObjectParts typeR_arm = Parts::kRight_arm;
	static constexpr int PartsNum = static_cast<int>(Parts::kPartNum);

	enum class Behavior {
		kRoot,
		kAttack,
		kDash,
		kJump,
	};

	enum class AttackPhase {
		kAticipation,
		kCharge,
		kSwing,
	};

	struct ConstAttack {
		int32_t anticipationTime;
		int32_t chargeTime;
		int32_t swingTime;
		int32_t recoveryTime;
		float anticipationSpeed;
		float chargeSpeed;
		float swingSpeed;
	};

	// 攻撃用ワーク
	struct WorkAttack {
		int32_t attackParameter_ = 0;
		int32_t comboIndex = 0;
		int32_t inComboPhase = 0;
		bool comboNext = false;
	};

	// ダッシュ用ワーク
	struct WorkDash {
		// ダッシュ用の媒介変数
		int32_t dashParameter_;
	};

	// コンボの数
	static const int ComboNum = 3;

	// コンボ定数表
	static const std::array<ConstAttack, ComboNum> kConstAttacks_;

public: // メンバ関数
	/// 初期化
	void Initialize(std::vector<Model*> models, ViewProjection* viewProjection) override;

	/// 更新
	void Update() override;

	/// 描画
	void Draw() override;

	void OnCollision([[maybe_unused]] Collider* other) override;

	/// 中心座標を取得
	Vector3 GetCenterPosition() const override;

	void SetLockOn(const LockOn* lockOn) { this->lockOn_ = lockOn; }

	void SetHammer(Hammer* hammer) { this->hammer_ = hammer; }

private:

	/// 各ワールドトランスフォーム初期化
	void InitializeWorldTransform();

	/// 浮遊ギミック初期化
	void InitializeFloatingGimmick();	

#pragma region 各ふるまい初期化
	void BehaviorRootInitialize();   // 通常行動
	void BehaviorAttackInitialize(); // 攻撃行動
	void BehaviorDashInitialize();   // ダッシュ行動
	void BehaviorJumpInitialize();   // ジャンプ行動
	void InitializeBehavior();       // ふるまい初期化
#pragma endregion

#pragma region 移動処理

	// キーボード操作
	bool KeyboradController(const float deadZone);

	// ゲームパッド操作
	bool GamePadController(const float deadZone);

	/// ジョイスティックによる座標の移動
	void JoyStickMove(const float speed);

#pragma endregion

#pragma region 浮遊

	void UpdateFloatingGimmick(); // 浮遊ギミック更新
	void PartAnimation(float parameter); //パーツのアニメーション

#pragma endregion 

#pragma region 各ふるまい更新
	void BehaviorRootUpdate();  //通常行動
	void BehaviorAttackUpdate();//攻撃行動
	void BehaviorDashUpdate();  //ダッシュ行動
	void BehaviorJumpUpdate();  //ジャンプ行動
	void UpdateBehavior();      //ふるまい更新
#pragma endregion

	// 攻撃行動時の更新
	void UpdateAticipation();// 振りかぶり処理
	void UpdateCharge(); // 溜め行動
	void UpdateSwing(); // 振り下ろし処理

	/// デバッグテキスト描画
	void DrawDebugText();

	/// 調整項目の適用
	void ApplyGlobalVariables();

private: // メンバ変数

	Input* input_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};
	bool isMoving = false;

	// 目標角度
	Vector3 targetRotate_ = {};

	/// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	/// 浮遊移動のサイクル<frame>
	static inline int32_t cycle_ = 90;
	/// 浮遊の振幅
	static inline float amplitube = 0.2f;
	static inline float armAngle_ = 0.5f;

	// ふるまい
	Behavior behavior_ = Behavior::kRoot;
	// ふるまいのリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	// 攻撃フェーズ
	AttackPhase attackPhase_ = AttackPhase::kAticipation;

	// 攻撃用ワーク
	WorkAttack workAttack_;

	// ダッシュ用ワーク
	WorkDash workDash_;
	// 補間レート
	float destinationAngleY = 0.1f;

	static void (Player::*behaviorInitializeTable[])();
	static void (Player::*attackTable[])();
	static void (Player::*behaviorUpdateTable[])();

	// ロックオン
	const LockOn* lockOn_ = nullptr;
	float speed_ = {};

	// ハンマー
	Hammer* hammer_;
};
