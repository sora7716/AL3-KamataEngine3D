#pragma once
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/math/Math.h"
#include "input/Input.h"
#include <memory>
#include <vector>

/// <summary>
/// モデルのインターフェース
/// </summary>
class IModel {
public: // メンバ関数
	IModel() = default;
	// 純粋仮想関数
	virtual ~IModel() = default;
	virtual void DebugText() = 0;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	virtual void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label">ラベル</param>
	void DebugText(const char* label);

	/// <summary>
	/// 親子付け
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

	/// <summary>
	/// 浮遊ギミック初期化
	/// </summary>
	void InitializeFloatingGimmick();

	/// <summary>
	/// 浮遊ギミックの更新
	/// </summary>
	float UpdateFloatingGimmick();

	/// <summary>
	/// 三角波を使用したギミックの更新
	/// </summary>
	/// <returns></returns>
	float UpdateTriangleGimmick();

	/// <summary>
	/// 移動時のアニメーション
	/// </summary>
	float UpdateMoveAnimation();

	/// <summary>
	/// ノコギリ波
	/// </summary>
	/// <param name="interval">周期</param>
	/// <returns></returns>
	float Sawtooth(float interval = 2.0f * pi_f);

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	const WorldTransform& GetWorldTransform();

public://静的メンバ変数
protected: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
	// 浮遊ギミックの振幅
	float amplitude_ = {};
	// サイクル(どれくらいの感覚で動くか)
	int cycle_ = {};
	//どれくらい動かすか
	float wave_ = 2.0f * pi_f;
};
