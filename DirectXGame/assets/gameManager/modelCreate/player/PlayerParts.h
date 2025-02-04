#pragma once
#include "assets/gameManager/modelCreate/BaseModel.h"

/// <summary>
/// プレイヤーパーツ
/// </summary>
class PlayerParts:public BaseModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerParts() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
    ~PlayerParts()override = default;

protected: // メンバ変数
};

/// <summary>
/// 髪
/// </summary>
class Hair : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 顔
/// </summary>
class Face : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 眉毛
/// </summary>
class EyeBrows : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 体
/// </summary>
class Body : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 左もも
/// </summary>
class LeftThigh : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 左足
/// </summary>
class LeftLeg : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 右もも
/// </summary>
class RightThigh : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 右足
/// </summary>
class RightLeg : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 服(上)
/// </summary>
class UpperCloth : public PlayerParts {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UpperCloth() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UpperCloth() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 服(下)
/// </summary>
class LowerCloth : public PlayerParts {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LowerCloth() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LowerCloth() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 左腕
/// </summary>
class LeftArm: public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};

/// <summary>
/// 右腕
/// </summary>
class RightArm : public PlayerParts {
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
};
