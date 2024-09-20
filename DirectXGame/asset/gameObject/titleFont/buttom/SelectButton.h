#pragma once
#include "ISelectButton.h"

/// <summary>
/// スタートのボタン
/// </summary>
class StartButton : public ISelectButton {
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

private: // メンバ関数

	/// <summary>
	/// 選択時のアニメーション
	/// </summary>
	void Animation();

private: // メンバ変数
	float positionY_ = 0.0f;//現在の位置
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

private: // メンバ関数
	/// <summary>
	/// 選択時のアニメーション
	/// </summary>
	void Animation();

private:                     // メンバ変数
	float positionY_ = 0.0f; // 現在の位置
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

/// <summary>
/// ルールのボタン
/// </summary>
class SelectButton : public ISelectButton {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SelectButton() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectButton() = default;

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

private:                    // メンバ変数
	float positionY = 0.0f; // Y座標
};

//セレクトキー(W)の背景
class SelectKeyW_Back : public ISelectButton{

public:

	SelectKeyW_Back() = default;

	~SelectKeyW_Back() = default;

	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;


};

//セレクトキー(W)の文字
class SelectKeyW_Moji : public ISelectButton {

public:
	SelectKeyW_Moji() = default;

	~SelectKeyW_Moji() = default;

	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};

// セレクトキー(S)の背景
class SelectKeyS_Back : public ISelectButton {

public:
	SelectKeyS_Back() = default;

	~SelectKeyS_Back() = default;

	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};

// セレクトキー(S)の文字
class SelectKeyS_Moji : public ISelectButton {

public:
	SelectKeyS_Moji() = default;

	~SelectKeyS_Moji() = default;

	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};

// セレクトキー(ESC)の背景
class SelectKeyESC_Back : public ISelectButton {

public:
	SelectKeyESC_Back() = default;

	~SelectKeyESC_Back() = default;

	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;
};

// セレクトキー(ESC)の文字
class SelectKeyESC_Moji : public ISelectButton {

public:
	SelectKeyESC_Moji() = default;

	~SelectKeyESC_Moji() = default;

	void Initialize(Model* model, ViewProjection* viewProjection) override;

	void Update() override;

	void Draw() override;

private:
	/// <summary>
	/// 選択時のアニメーション
	/// </summary>
	void Animation();
private:                     // メンバ変数
	float positionX_ = 0.0f; // 現在の位置
};