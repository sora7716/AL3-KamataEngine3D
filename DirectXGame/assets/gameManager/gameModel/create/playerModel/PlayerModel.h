#pragma once
#include "assets/gameManager/gameModel/create/IModel.h"

class IPlayerModel : public IModel {
public: // 列挙型
	enum class Behavior {
		kRoot,
		kBlow,
	};

public: //メンバ関数
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// タイマーの設定
	/// </summary>
	void ChangeTime();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
protected: // メンバ関数
	// 純粋仮想関数
	virtual void BehaviorRootReset();
	virtual void BehaviorBlowReset();
	virtual void BehaviorRootUpdate() = 0;
	virtual void BehaviorBlowUpdate() = 0;
	// 関数ポインタの配列
	//リセット
	static void (IPlayerModel::*ResetTable[])();
	//更新
	static void (IPlayerModel::*BehaviorTable[])();

public://静的メンバ変数
	static inline const float kMaxTimer_ = 30.0f;//時間の上限
private: // メンバ変数
	// 振る舞い
	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	//切り替えタイマー
	float changeTimer_ = 0.0f;
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
	void BehaviorRootUpdate()override;

	/// <summary>
	/// 打撃
	/// </summary>
	void BehaviorBlowUpdate()override;
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
	/// 通常行動用
	/// </summary>
	void BehaviorRootUpdate();

	/// <summary>
	/// 打撃用
	/// </summary>
	void BehaviorBlowUpdate();
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
	void BehaviorRootUpdate();

	/// <summary>
	/// 打撃用
	/// </summary>
	void BehaviorBlowUpdate();
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

public: // メンバ変数
	std::vector<IPlayerModel*> parts_ = {nullptr};

	WorldTransform worldTransform_;
};