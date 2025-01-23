#pragma once
#include "WorldTransform.h"
#include "memory"

// 前方宣言
class Model;
class ViewProjection;
class OBB;

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
	/// ワイヤーの描画
	/// </summary>
	void DrawWire();

	/// <summary>
	/// 取得時処理
	/// </summary>
	void OnCollision();

	/// <summary>
	/// デバッグテキスト
	/// </summary>
	/// <param name="label">ラベル</param>
	void DebugText(const char* label);

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPos();

	/// <summary>
	/// ワイヤーフレームのGetter
	/// </summary>
	/// <returns></returns>
	OBB* GetWireFrame();

	/// <summary>
	/// スペルカード取得のSetter
	/// </summary>
	/// <param name="isRetrieve"></param>
	void SetIsSpellCardGet(bool isSpellCardGet);

private://メンバ関数

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void InitializeAnimation();

	/// <summary>
	/// 浮遊ギミックの更新
	/// </summary>
	float UpdateFloatingGimmick();

	/// <summary>
	/// スペルカード未取得時の処理
	/// </summary>
	void Idol();

private: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	std::unique_ptr<OBB> wireFrame_ = nullptr;
	bool isSpellCardGet_ = false; // スペルカードが取得されたかどうか
	float floatingParameter_ = {};
	float amplitube = {};
	int cycle_ = {};
	float angleTimer_ = {};
};
