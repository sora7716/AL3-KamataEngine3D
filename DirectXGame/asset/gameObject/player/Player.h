#pragma once
#include "WorldTransform.h"
#include "asset/math/Aithmetic.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// プレイヤー
/// </summary>
class Player {

public://列挙型

	//プレイヤーの状態
	enum class Phase {
		kStart,//始まり
		kPlay,//ゲームプレイ
		kDeth,//死亡
	};

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() = default;

    /// <summary>
	/// デストラクタ
    /// </summary>
	~Player() = default;

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
	/// 描画
	/// </summary>
	void Draw();

#pragma region コマンド
	/// <summary>
	/// 右方向移動
	/// </summary>
	void MoveRight();

	/// <summary>
	/// 左方向移動
	/// </summary>
	void MoveLeft();

	/// <summary>
	/// 上方向移動
	/// </summary>
	void MoveUp();

	/// <summary>
	/// 下方向移動
	/// </summary>
	void MoveDown();
#pragma endregion

	/// <summary>
	/// 親子関係作る
	/// </summary>
	void SetPearent(const WorldTransform* parent);

    /// <summary>
    /// ワールドトランスのゲッター
    /// </summary>
    /// <returns></returns>
	WorldTransform& GetWorldTransform();

public://静的メンバ変数

	///キャラクターの移動速度
	static inline const float kCharacterSpeed = 0.2f;

private://メンバ変数

	///モデル
	Model* model_ = nullptr;

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_;

	//速度
	Vector3 velocity_ = {};

	//プレイヤーの状態
	Phase phase_ = Phase::kStart;
};
