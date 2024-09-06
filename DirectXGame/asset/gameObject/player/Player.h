#pragma once
#include "WorldTransform.h"
#include "asset/math/Aithmetic.h"
#include "asset/math/collision/Collision.h"
#include "asset/gameObject/player/playerParts/PlayerParts.h"

//前方宣言(苦肉の策)
class ViewProjection;
class Create;

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public://列挙型

	// プレイヤーの状態
	enum class Phase {
		kStart, // 始まり
		kPlay,  // ゲームプレイ
		kDeth,  // 死亡
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
	void Initialize(Create* create, ViewProjection* viewProjection);

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
	/// プレイヤーの動ける上限
	/// </summary>
	void MoveLimit();

	/// <summary>
	/// 親子関係作る
	/// </summary>
	void SetPearent(const WorldTransform* parent);

	/// <summary>
	/// 位置のセッター
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const Vector3& position); 

	/// <summary>
	/// 角度のセッター
	/// </summary>
	/// <param name="rotation">角度</param>
	void SetRotation(const Vector3& rotation);

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	AABB GetAABB();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform();

	/// <summary>
	/// パーツの位置のセッター
	/// </summary>
	/// <param name="partsType">パーツの場所</param>
	/// <param name="position">位置</param>
	void SetPartsPosition(IPlayerParts::PartsName partsType, const Vector3& position);

	/// <summary>
	/// パーツの角度のセッター
	/// </summary>
	/// <param name="partsType">パーツの場所</param>
	/// <param name="angle">角度</param>
	void SetPartsAngle(IPlayerParts::PartsName partsType, const Vector3& angle);

private://メンバ関数

	/// <summary>
	/// パーツを作る
	/// </summary>
	void CreateParts();

	/// <summary>
	/// パーツの初期化
	/// </summary>
	void InitializeParts();

public://静的メンバ変数

	///キャラクターの移動速度
	static inline const float kCharacterSpeed = 0.2f;
	// オブジェクトの衝突判定のサイズ
	static inline const float kWidth = 3.0f;  // 横幅
	static inline const float kHeight = 3.0f; // 立幅
	static inline const float kDepth = 2.0f;  // 深さ

private://メンバ変数

	///ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_;

	//速度
	Vector3 velocity_ = {};

	//プレイヤーの状態
	Phase phase_ = Phase::kStart;

	//パーツ
	std::unique_ptr<IPlayerParts> parts_[IPlayerParts::PartsNum] = {nullptr};

	// クリエイトクラス
	Create* create_ = nullptr; 
};
