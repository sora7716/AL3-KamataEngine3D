#pragma once
#include "ISelectButton.h"

/// <summary>
/// スタートのボタン
/// </summary>
class StartButton:public ISelectButton {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StartButton() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StartButton() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="create"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model* model, ViewProjection* viewProjection)override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};

/// <summary>
/// スタートのボタン
/// </summary>
class StartBackButton : public ISelectButton {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StartBackButton() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StartBackButton() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="create"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};

/// <summary>
/// ルールのボタン
/// </summary>
class RuleBackButton : public ISelectButton {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RuleBackButton() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RuleBackButton() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="create"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};

/// <summary>
/// ルールのボタン
/// </summary>
class RuleButton : public ISelectButton {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RuleButton() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RuleButton() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="create"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
};