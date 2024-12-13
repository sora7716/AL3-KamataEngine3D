#pragma once
#include "Vector2.h"
#include "assets/gameManager/gameModel/create/mimicModel/MimicModel.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"
#include "assets/gameManager/scene/game/battle/gameObject/ui/LifeBar/LifeBar.h"

// 前方宣言
class Player;
class LifeBar;
class Create;

/// <summary>
/// ミミックのクラス
/// </summary>
class Mimic : public BaseCharacter {
public: // 列挙型
	enum class Status {
		kIdle,
		kMove,   // 移動
		kMoveToward,  // 追跡
		kAttack, // 攻撃
		kCoolDown //攻撃のあと一旦止まる
	};

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Mimic() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Mimic() = default;

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
	/// プレイヤーのセッター
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player);

	/// <summary>
	/// キャラクタータイプのゲッター
	/// </summary>
	/// <returns></returns>
	int GetCharacterType() { return (int)charType_; }
	
	/// <summary>
	/// ダメージを受けた処理
	/// </summary>
	void TookDamage() { mimicLifeBar_->TookDamage(); }

	/// <summary>
	/// 2D描画
	/// </summary>
	void DrawSprite() { mimicLifeBar_->Draw(); }
private: // メンバ関数
	/// <summary>
	/// ターゲットに向かって移動
	/// </summary>
	/// <param name="target"></param>
	void MoveToward();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	//待機
	void Idle();

	/// <summary>
	/// ミミックのステータスを変更
	/// </summary>
	void ChangeStatus();

	//向き
	void Direction();

	//攻撃後のクールダウン
	void CoolDown();

	void BehaviorRootReset();
	void BehaviorRootUpdate();

	void BehaviorBiteReset();
	void BehaviorBiteUpdate();

public: // 静的メンバ変数と関数テーブル

	//敵の移動速度
	static inline const float kSpeed = 1.0f;
	// 敵の視界範囲
	static inline const float kChaseRange = 20.0f;
	// 攻撃範囲
	static inline const float kAttackRange = 2.0f;
	// 行動のテーブル
	static void (Mimic::*ActionModeTable[])();
	static void (Mimic::*AnimationTable[])();
	//待機時間のインターバル
	static inline const float kWaitInterval = 120;
	//クールダウン時間のインターバル
	static inline const float kCoolDownInterval = 60;

private: // メンバ変数
	std::unique_ptr<MimicModel> mimicModel_ = nullptr;
	Vector2 circulaMoveRadius_ = {};
	Vector3 center = {};
	Vector3 velocity_ = {};

	// 攻撃用の変数
	bool isAttacking = false;
	//プレイヤー
	Player* player_ = nullptr;
	// ステータス
	int status_ = (int)Status::kIdle; 
	//待機時間
	float waitTime_ = 0.0f;
	//クールダウン時間
	float coolTime_ = 0.0f;
	//待機時の最初のアングルを決定するフラグ
	bool isSetStartAngle_ = false;
	//最初のアングル
	float startAngle_ = 0.0f;
	//アングルタイマー
	float angleTimer_ = 0.0f;
	//BehaviorRootUpdate用
	float frame_ = 0.0f;

	//ライフバー
	std::unique_ptr<LifeBar> mimicLifeBar_ = nullptr;
	bool isDead_ = false;
};