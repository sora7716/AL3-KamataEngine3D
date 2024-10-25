#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"

class Input;
class Player;

/// <summary>
/// レールカメラ
/// </summary> 
class RailCamera : public Math{

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
	/// <param name="viewProjection">もともとあったビュープロジェクション</param>
	void Initialize(ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

    /// <summary>
    /// リセット
    /// </summary>
    void Reset();

	/// <summary>
	/// 対象ターゲットのsetter
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(const WorldTransform* target);

	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	const ViewProjection* GetViewProjection() { return viewProjection_; }


private:
	void JoyStickRotation();

	// オフセット計算
	Vector3 CalcOffset() const;

private:
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	// 追従対象
	const WorldTransform* target_ = nullptr;

	Input* input_ = nullptr;

	// 追従対象の残像座標
	Vector3 interTarget_ = {};

	float desticationAngleY = 0.0f;

	Player* player_ = nullptr;

};
