#pragma once
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
		kObjectNum   // オブジェクトの数
	};
	using ObjectType = Type;
	static inline ObjectType typeStart = Type::kStart;           // スタートの文字
	static inline ObjectType typeStart_Back = Type::kStart_Back; // スタートの背景
	static inline ObjectType typeRule = Type::kRule;             // ルールの文字
	static inline ObjectType typeRule_Back = Type::kRule_Back;   // ルールの背景
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

protected: // メンバ変数
	//モデル
	Model* model_= nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//フレーム
	float frame_ = 0.0f;

	//線形補間を開始するかのフラグ
	bool isButtonLerp_ = false;
};