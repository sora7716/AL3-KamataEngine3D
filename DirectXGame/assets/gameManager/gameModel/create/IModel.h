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
	virtual void Initialize(Model* model, ViewProjection* viewProjection);
	virtual void Update();
	virtual void DebugText() = 0;
	virtual void Draw();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label">ラベル</param>
	virtual void DebugText(const char* label);

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
};
