#pragma once
#include "WorldTransform.h"

// 前方宣言
class ViewProjection;
class Model;

/// <summary>
/// プレイヤー
/// </summary>
class Player {
public: // メンバ関数
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
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform();

	/// <summary>
	/// ビュープロジェクションのセッター
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetViewProjection(const ViewProjection* viewProjection);

private://メンバ関数
	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	void GamePadControl();

	/// <summary>
	/// キーボードの操作
	/// </summary>
	void KeyBoaeredControl();

private: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
	const ViewProjection* directionViewProjection_ = nullptr;

	Vector3 move_{};//移動量
	bool isMove_ = false;//移動したかどうかのフラグ
	const float speed_ = 0.3f;//速度
};
