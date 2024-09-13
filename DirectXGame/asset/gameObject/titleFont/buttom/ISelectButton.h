#pragma once
#include "TextureManager.h"
#include "WorldTransform.h"
#include "asset/math/Math.h"

// 前方宣言
class Model;
class ViewProjection;

class ISelectButton {
public: // 列挙型
	enum class Type {
		kStart_Back, // スタートの背景
		kStart,      // スタートの文字
		kRule_Back,  // ルールの背景
		kRule,       // ルールの文字
		kSelectButton,//セレクトする用のボタン
		kObjectNum   // オブジェクトの数
	};
	using ObjectType = Type;
	static inline ObjectType typeStart = Type::kStart;           // スタートの文字
	static inline ObjectType typeStart_Back = Type::kStart_Back; // スタートの背景
	static inline ObjectType typeRule = Type::kRule;             // ルールの文字
	static inline ObjectType typeRule_Back = Type::kRule_Back;   // ルールの背景
	static inline ObjectType typeSelectButton = Type::kSelectButton; // セレクトする用のボタン
	static inline const uint32_t kButtonNum = static_cast<uint32_t>(Type::kObjectNum);

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ISelectButton() = default;

	// 純粋仮想関数
	virtual ~ISelectButton() = default;
	virtual void Initialize(Model* create, ViewProjection* viewProjection) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// 親子付け
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// ボタンの線形補間
	/// </summary>
	void ButtonLerp();

	/// <summary>
	/// ボタンの線形補間フラグのセッター
	/// </summary>
	/// <param name="isBottonLarp">ボタンの線形補間フラグ</param>
	void SetIsButtonLarp(bool isBottonLarp);

	/// <summary>
	/// フレーム
	/// </summary>
	/// <param name="frame">フレーム</param>
	void SetFrame(float frame);

	/// <summary>
	/// 色を変えるフラグのセッター
	/// </summary>
	/// <param name="isSelectChangeColor"></param>
	void SetIsSelectChangeColor(bool isSelectChangeColor) { isSelectChangeColor_ = isSelectChangeColor; }

	/// <summary>
	/// 現在がルールシーンかどうかのフラグ
	/// </summary>
	/// <param name="isRuleSceneNow"></param>
	void SetIsRuleSceneNow(bool isRuleSceneNow) { isRuleSceneNow_ = isRuleSceneNow; }
	
	/// <summary>
	/// 上を選択したときのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsSelectStart() { return isSelectStart_; }

	/// <summary>
	/// 下を選択したときのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsSelectRule() { return isSelectRule_; }

	/// <summary>
	/// ゲームスタートのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsGameStart() { return isGameStart_; }

	/// <summary>
	/// ゲームルールのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsGameRule() { return isGameRule_; }

protected: // メンバ変数
	//モデル
	Model* model_= nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//テクスチャ
	uint32_t textureHandle_ = TextureManager::Load("change_color.png");
	//フレーム
	float frame_ = 0.0f;

	//線形補間を開始するかのフラグ
	bool isButtonLerp_ = false;

	bool isGameStart_ = false;//ゲームをスタートするかどうか
	bool isGameRule_ = false;//ゲームルールをスタートするかどうか
	bool isSelectChangeColor_ = false;//色を変えるフラグ
	bool isSelectStart_ = false;//上を選択
	bool isSelectRule_ = false;//下を選択
	bool isButtonBack_ = false;//ボタンを戻す
	bool isRuleSceneNow_ = false;//現在がルールシーンなのかのフラグ
};