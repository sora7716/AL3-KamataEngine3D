#pragma once
#include "assets/gameManager/gameModel/create/IModel.h"

/// <summary>
/// 蓋
/// </summary>
class Lid : public IModel {
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
};

/// <summary>
/// 目
/// </summary>
class Eye : public IModel {
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
};

/// <summary>
/// 箱
/// </summary>
class Box : public IModel {
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
};

/// <summary>
/// 舌
/// </summary>
class Tongue : public IModel {
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
};

/// <summary>
/// 歯(上)
/// </summary>
class ToothUp : public IModel {
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
};

/// <summary>
/// 歯(下)
/// </summary>
class ToothBottom : public IModel {
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

private: // メンバ変数
	std::vector<IModel*> parts = {nullptr};
};