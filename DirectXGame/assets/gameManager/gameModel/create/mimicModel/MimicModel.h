#pragma once
#include "assets/gameManager/gameModel/create/IModel.h"

/// <summary>
/// プレイヤーモデルのインターフェース
/// </summary>
class IMimicModel : public IModel {
public: // 列挙型
	enum class Behavior {
		kRoot, // 通常
		kBite, // 打撃
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
	/// 攻撃時の初期化
	/// </summary>
	virtual void BehaviorBiteReset();

	// 純粋仮想関数
	virtual void BehaviorRootUpdate() = 0;
	virtual void BehaviorBiteUpdate() = 0;
	// 関数ポインタの配列
	// リセット
	static void (IMimicModel::* ResetTable[])();
	// 更新
	static void (IMimicModel::* BehaviorTable[])();

private: // メンバ変数
	// 振る舞い
	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	// アクションタイマー
	float actionTimer_ = 0.0f;
};

/// <summary>
/// 蓋
/// </summary>
class Lid : public IMimicModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Lid() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Lid() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void BehaviorBiteUpdate();
};

/// <summary>
/// 目
/// </summary>
class Eye : public IMimicModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Eye() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Eye() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void BehaviorBiteUpdate();
};

/// <summary>
/// 箱
/// </summary>
class Box : public IMimicModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Box() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Box() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void BehaviorBiteUpdate();
};

/// <summary>
/// 舌
/// </summary>
class Tongue : public IMimicModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tongue() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tongue() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void BehaviorBiteUpdate();
};

/// <summary>
/// 歯(上)
/// </summary>
class ToothUp : public IMimicModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ToothUp() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ToothUp() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void BehaviorBiteUpdate();
};

/// <summary>
/// 歯(下)
/// </summary>
class ToothBottom : public IMimicModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ToothBottom() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ToothBottom() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 通常
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void BehaviorBiteUpdate();
};

/// <summary>
/// ミミックのモデル
/// </summary>
class MimicModel {
public: // 列挙型
	enum class Parts { 
		kBox, 
		kLid, 
		kEye, 
		kToothUp, 
		kToothBottom, 
		kTongue, 
		kPartsNum 
	};

public:  // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MimicModel() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MimicModel();

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
	/// 親子付け
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform*parent);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="behavior"></param>
	void SetBehavior(IMimicModel::Behavior behavior);

	IMimicModel::Behavior GetBehavior();

private: // メンバ変数
	std::vector<IMimicModel*> parts_ = {nullptr};
};

// Behaviorのモード用のエイリアス
using BehaviorMode = IMimicModel::Behavior;