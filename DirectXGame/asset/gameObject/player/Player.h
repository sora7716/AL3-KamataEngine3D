#pragma once
#include "WorldTransform.h"

// 前方宣言
class Model;
class ViewProjection;
class Input;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="texture">テクスチャ</param>
	void Initialize(Model* model, ViewProjection* viewProjection, uint32_t texture);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private://メンバ関数
#ifdef _DEBUG
	void DebugText();
#endif // _DEBUG

private:                                       // メンバ変数
	Model* model_ = nullptr;                   // モデル
	ViewProjection* viewProjection_ = nullptr; // ビュープロジェクション
	WorldTransform worldTransform_;            // ワールドトランスフォーム
	uint32_t texture_ = 0u;                    // テクスチャ
	Input* input_ = nullptr;                   // キー入力
};
