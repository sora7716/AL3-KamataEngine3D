#pragma once
#include "WorldTransform.h"
#include <memory>
#include <vector>
// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// プレイヤーの体のインターフェース
/// </summary>
class IPlayerModel {
public: // メンバ関数
	IPlayerModel() = default;
	// 純粋仮想関数
	virtual ~IPlayerModel() = default;
	virtual void Initialize(Model* model, ViewProjection* viewProjection) = 0;
	virtual void Update() = 0;
	virtual void DebugText() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label">ラベル</param>
	void DebugText(const char* label);

	/// <summary>
	/// 親子付け
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	const WorldTransform& GetWorldTransform();

protected: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
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
	void DebugText()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
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
	void DebugText()override;

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
	void DebugText()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
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
/// プレイヤーのモデル
/// </summary>
class PlayerModel {
public://列挙型と静的メンバ変数

	//パーツの場所と数
	enum class Parts {
		kHead,
		kBody,
		kRightArm,
		kLeftArm,
		kPartsNum,
	};

	//パーツの数
	static inline const int PARTS_NUM = (int)Parts::kPartsNum;

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerModel() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerModel() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection);

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
	std::vector<IPlayerModel*> iPlayerModels_ = {nullptr};
};