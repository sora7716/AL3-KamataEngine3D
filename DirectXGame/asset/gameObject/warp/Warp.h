#pragma once
#include "WorldTransform.h"

//前方宣言(苦肉の策)
class Model;
class ViewProjection;

/// <summary>
/// ワープのクラス
/// </summary>
class Warp {
public://メンバ関数
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Warp() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Warp() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="isSpawn">ワープポイントを出すかどうかのフラグ</param>
	void Update(bool isSpawn);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 親子関係を築づく
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform*parent);

	/// <summary>
	/// サイズのセッター
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(float size);

private: // メンバ関数
	/// <summary>
	///スポーン
	/// </summary>
	void Spawn();

private://メンバ変数
	Model* model_ = nullptr;//モデル
	ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション
	WorldTransform worldTransform_;//ワールドトランスフォーム
	float size_ = 0.0f;//サイズ
	float sizeEasing_ = 0.0f;//イージングのフレーム
	bool isAlive_ = false;
};