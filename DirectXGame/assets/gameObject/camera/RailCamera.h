#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"

class Input;

/// <summary>
/// レールカメラ
/// </summary> 
class RailCamera {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	RailCamera() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RailCamera() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="matWorld">ワールド座標</param>
	/// <param name="radian">回転角[ラジアン]</param>
	/// <param name="viewProjection">もともとあったビュープロジェクション</param>
	void Initialize(ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	const ViewProjection* GetViewProjection();

	void SetTarget(const WorldTransform* target) { target_ = target; }

private:

	void JoyStickRotation();

private: // メンバ変数

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	// 追従対象
	const WorldTransform* target_ = nullptr;

	Input* input_ = nullptr;

};
