#pragma once
#include "assets/gameManager/gameModel/create/IModel.h"

/// <summary>
/// プレイヤーモデルのインターフェース
/// </summary>
class IPlayerModel : public IModel {
public: // 列挙型
	enum class Behavior {
		kRoot, // 通常
		kBlow, // 打撃
		kDash, // ダッシュ
	};

public: // メンバ関数
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// 行動タイマーのセッター
	/// </summary>
	void SetActionTimer(float actionTime);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ふるまいのセッター
	/// </summary>
	/// <param name="behavior">ふるまい</param>
	void SetBehaviorRequest(const Behavior& behavior);

	/// <summary>
	/// ふるまいのゲッター
	/// </summary>
	/// <returns>ふるまい</returns>
	Behavior GetBehavior();

	/// <summary>
	/// アクションタイマーのゲッター
	/// </summary>
	/// <returns>アクションタイマー</returns>
	float GetActionTimer();

protected: // メンバ関数
	/// <summary>
	/// 通常時の初期化
	/// </summary>
	virtual void BehaviorRootReset();

	/// <summary>
	/// 打撃時の初期化
	/// </summary>
	virtual void BehaviorBlowReset();

	/// <summary>
	/// ダッシュ時の初期化
	/// </summary>
	virtual void BehaviorDashReset();

	// 純粋仮想関数
	virtual void BehaviorRootUpdate() = 0;
	virtual void BehaviorBlowUpdate() = 0;
	virtual void BehaviorDashUpdate() = 0;
	// 関数ポインタの配列
	// リセット
	static void (IPlayerModel::*ResetTable[])();
	// 更新
	static void (IPlayerModel::*BehaviorTable[])();

private: // メンバ変数
	// 振る舞い
	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	// アクションタイマー
	float actionTimer_ = 0.0f;
};

/// <summary>
/// 頭
/// </summary>
class Head : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Head() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Head() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate() override;

	/// <summary>
	/// 打撃
	/// </summary>
	void BehaviorBlowUpdate() override;

	/// <summary>
	/// ダッシュ時の更新
	/// </summary>
	void BehaviorDashUpdate() override;
};

/// <summary>
/// 体
/// </summary>
class Body : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Body() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Body() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate() override;

	/// <summary>
	/// 打撃
	/// </summary>
	void BehaviorBlowUpdate() override;

	/// <summary>
	/// ダッシュ時の更新
	/// </summary>
	void BehaviorDashUpdate() override;
};

/// <summary>
/// 右腕
/// </summary>
class RightArm : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RightArm() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RightArm() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 通常行動の更新
	/// </summary>
	void BehaviorRootUpdate() override;

	/// <summary>
	/// 打撃の更新
	/// </summary>
	void BehaviorBlowUpdate() override;

	/// <summary>
	/// 打撃用の初期化
	/// </summary>
	void BehaviorBlowReset() override;

	/// <summary>
	/// ダッシュの更新
	/// </summary>
	void BehaviorDashUpdate() override;
};

/// <summary>
/// 左腕
/// </summary>
class LeftArm : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LeftArm() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LeftArm() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 通常行動用
	/// </summary>
	void BehaviorRootUpdate()override;

	/// <summary>
	/// 打撃用
	/// </summary>
	void BehaviorBlowUpdate()override;

	/// <summary>
	/// 打撃用の初期化
	/// </summary>
	void BehaviorBlowReset() override;

	/// <summary>
	/// ダッシュ時の更新
	/// </summary>
	void BehaviorDashUpdate() override;
};

/// <summary>
/// プレイヤーのモデル
/// </summary>
class PlayerModel {
public: // 列挙型と静的メンバ変数
	// パーツの場所と数
	enum class Parts {
		kBody,
		kHead,
		kRightArm,
		kLeftArm,
		kStaff,
		kPartsNum,
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerModel() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerModel();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 親のセッター
	/// </summary>
	/// <param name="worldTransform"></param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// 振る舞いのセッター
	/// </summary>
	/// <param name="behavior">振る舞い1</param>
	void SetBehaviorRequest(const IPlayerModel::Behavior& behavior);

	/// <summary>
	/// ふるまいのゲッター
	/// </summary>
	/// <returns></returns>
	IPlayerModel::Behavior GetBehavior();

	/// <summary>
	/// モーションの継続時間のリセット
	/// </summary>
	void SetActionTime(float actionTime);

	/// <summary>
	/// アクションタイマーのゲッター
	/// </summary>
	/// <returns>actionTimer</returns>
	float GetActionTimer();

public: // メンバ変数
	std::vector<IPlayerModel*> parts_ = {nullptr};

	WorldTransform worldTransform_;
};

// Behaviorのモード用のエイリアス
using BehaviorMode = IPlayerModel::Behavior;