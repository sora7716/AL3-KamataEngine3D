#pragma once
#include "assets/gameManager/gameModel/create/IModel.h"

/// <summary>
/// 頭
/// </summary>
class Head : public IModel {
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
};

/// <summary>
/// 体
/// </summary>
class Body : public IModel {
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
};

/// <summary>
/// 右腕
/// </summary>
class RightArm : public IModel {
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
/// 左腕
/// </summary>
class LeftArm : public IModel {
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
	void Initialize(std::vector<Model*>&& models,ViewProjection* viewProjection);

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
	std::vector<IModel*> parts_ = {nullptr};
};