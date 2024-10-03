#pragma once
#include "IPlayerParts.h"

/// <summary>
/// プレイヤーパーツ(体)
/// </summary>
class PlayerBody : public IPlayerParts {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerBody() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBody() override = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

///============================================================================================================================================

/// <summary>
/// プレイヤーパーツ(頭)
/// </summary>
class PlayerHead : public IPlayerParts {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerHead() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHead() override = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

};

///============================================================================================================================================

/// <summary>
/// プレイヤーパーツ(左上腕)
/// </summary>
class PlayerLeft_UpperArm : public IPlayerParts {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerLeft_UpperArm() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerLeft_UpperArm() override = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

///============================================================================================================================================

/// <summary>
/// プレイヤーパーツ(左腕)
/// </summary>
class PlayerLeft_LowerArm : public IPlayerParts {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerLeft_LowerArm() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerLeft_LowerArm() override = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

///============================================================================================================================================

/// <summary>
/// プレイヤーパーツ(左もも)
/// </summary>
class PlayerLeft_Thigh : public IPlayerParts {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerLeft_Thigh() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerLeft_Thigh() override = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};

///============================================================================================================================================

/// <summary>
/// プレイヤーパーツ(左足)
/// </summary>
class PlayerLeft_Leg : public IPlayerParts {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerLeft_Leg() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerLeft_Leg() override = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
};