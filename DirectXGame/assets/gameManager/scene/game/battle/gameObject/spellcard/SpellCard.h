#pragma once
#include "WorldTransform.h"

// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// スペルカード
/// </summary>
class SpellCard {

public:// メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpellCard() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpellCard() = default;
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model*model,ViewProjection *viewProjection);
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Draw(uint32_t textureHandle);

	/// <summary>
	/// デバッグテキスト
	/// </summary>
	/// <param name="label">ラベル</param>
	void DebugText(const char* label);

private: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;

};
