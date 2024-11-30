#pragma once
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/math/Math.h"
#include "assets/math/easing/Easing.h"
#include "input/Input.h"
#include <memory>
#include <vector>

/// <summary>
/// モデルのインターフェース
/// </summary>
class IModel {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
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
	///  アニメーションに使用する変数の初期化
	/// </summary>
	void InitializeAnimation();

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
	/// サイン波と線形補間を利用したアニメーション
	/// </summary>
	/// <param name="mode">イージングのモード</param>
	/// <returns>角度</returns>
	float LerpAnimation(const EasingMode& mode);

	/// <summary>
	/// 三角波と線形補間を利用したアニメーション
	/// </summary>
	/// <param name="mode">イージングモード</param>
	/// <returns>角度</returns>
	float TriangleLerpAnimation(const EasingMode& mode);

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
	// どれくらい動かすか
	float wave_ = 2.0f * pi_f;

	// 回転
	// どれくらい動かすかのタイマー
	float angleTimer_ = 0.0f;
	// 最初のアングル
	float startAngle_ = -45.0f;
	// 最後のアングル
	float endAngle_ = 60.0f;
	// 周期となるタイマー
	float motionTime_ = 1.0f;
};
