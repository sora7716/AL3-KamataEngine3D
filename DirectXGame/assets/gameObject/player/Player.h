#pragma once
#include "assets/gameobject/BaseCharacter.h"
//#include "assets/gameobject/effect/HitEffect.h"

#include "assets/math/Math.h"
#include "memory"
#include "vector"
#include <optional>

class Input;
class LockOn;
class Hammer;

// プレイヤーパーツの列挙体
enum Parts {
	kBase,
	kBody,
	kHead,
	kLeft_arm,
	kRight_arm,
};

/// <summary>
/// 自キャラ
/// </summary>
class Player : public BaseCharacter, Math {

public:
	enum class Behavior {
		kRoot,
		kAttack,
		kDash,
		kJump,
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

	/// 各ふるまいの初期化
	void BehaviorRootInitialize();
	void BehaviorAttackInitialize();
	void BehaviorDashInitialize();
	void BehaviorJumpInitialize();
	void InitializeBehavior();


	// ゲームパッドによるコントローラ入力
	bool GamePadController();

	/// ジョイスティックによる座標の移動
	void JoyStickMove(const float speed);

	/// 浮遊ギミック更新
	void UpdateFloatingGimmick();

	/// 各ふるまいの更新
	void BehaviorRootUpdate();
	void BehaviorAttackUpdate();
	void BehaviorDashUpdate();
	void BehaviorJumpUpdate();
	void UpdateBehavior();

	/// デバッグテキスト描画
	void DrawDebugText();

	/// 調整項目の適用
	void ApplyGlobalVariables();

private: // メンバ変数

	Input* input_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};
	bool isMoving = false;
	Vector3 targetRotate_ = {};

	/// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	/// 浮遊移動のサイクル<frame>
	static inline int32_t cycle_ = 90;
	/// 浮遊の振幅
	static inline float amplitube = 0.2f;
	static inline float armAngle_ = 0.5f;

	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	WorkAttack workAttack_;

	WorkDash workDash_;
	float destinationAngleY = 0.1f;

	static void (Player::*behaviorInitializeTable[])();
	static void (Player::*behaviorUpdateTable[])();

	const LockOn* lockOn_ = nullptr;
	float speed_ = {};
	Hammer* hammer_;
};
