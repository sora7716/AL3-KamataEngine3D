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
	virtual void BehaviorRootUpdate();
	virtual void BehaviorBlowUpdate();
	virtual void BehaviorDashUpdate();

	/// <summary>
	/// 打撃時の切り替えタイマー
	/// </summary>
	void BlowChangeTimer();

public: // 静的メンバ変数と関数ポインタの配列
	// 打撃時の待機時間
	static inline const float kMaxBlowWaitTime = 0.3f;
	// 関数ポインタの配列
	// リセット
	static void (IPlayerModel::*ResetTable[])();
	// 更新
	static void (IPlayerModel::*BehaviorTable[])();

protected: // メンバ変数
	// アングルタイマーを加算させるか
	bool isAngleTimerAdd_ = true;
	// 待機時間を計測する
	float waitTime_ = 0.0f;
	// 待機時間を開始するかどうか
	bool isStartWait_ = false;
	// 今何秒
	float second_ = deltaTime;
	// イージングモード
	EasingMode easingMode_ = EasingMode::kInSine;

private: // メンバ変数
	// 振る舞い
	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	// アクションタイマー
	float actionTimer_ = 0.0f;
};

/// <summary>
/// 髪
/// </summary>
class Hair : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Hair() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Hair() = default;

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
/// 眉毛
/// </summary>
class EyeBrows : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EyeBrows() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EyeBrows() = default;

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
/// 顔
/// </summary>
class Face : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Face() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Face() = default;

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
	/// 通常行動用
	/// </summary>
	void BehaviorRootUpdate() override;

	/// <summary>
	/// 打撃用
	/// </summary>
	void BehaviorBlowUpdate() override;

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
};

/// <summary>
/// 左腿
/// </summary>
class LeftLeg : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LeftLeg() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LeftLeg() = default;

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
};

/// <summary>
/// 左脛
/// </summary>
class LeftThigh : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LeftThigh() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LeftThigh() = default;

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
};

/// <summary>
/// 右腿
/// </summary>
class RightLeg : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RightLeg() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RightLeg() = default;

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
};

/// <summary>
/// 右脛
/// </summary>
class RightThigh : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RightThigh() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RightThigh() = default;

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
};

/// <summary>
/// 服(上)
/// </summary>
class UpperClothing : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UpperClothing() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UpperClothing() = default;

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
};

/// <summary>
/// 服(下)
/// </summary>
class LowerClothing : public IPlayerModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowerClothing() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowerClothing() = default;

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
};

/// <summary>
/// プレイヤーのモデル
/// </summary>
class PlayerModel {
public: // 列挙型と静的メンバ変数
	// パーツの場所と数
	enum class Parts {
		kBody,
		kFace,
		kHair,
		kEyeBrows,
		kLeftArm,
		kRightArm,
		kLeftThigh,
		kLeftLeg,
		kRightThigh,
		kRightLeg,
		kUpperClothing,
		kLowerClothing,
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