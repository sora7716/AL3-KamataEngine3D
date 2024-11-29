#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "array"
#include "assets/math/Math.h"

/// <summary>
/// ヒットエフェクト
/// </summary>
class HitEffect : public Math{

public://メンバ関数

	//コンストラクタ
	HitEffect() = default;
	//デストラクタ
	~HitEffect() = default;
	//初期化
	void Initialize(Model* model, const Vector3& position);
	//更新
	void Update();
	//描画
	void Draw(const ViewProjection&viewProjection);

private://メンバ変数

	//モデルデータ
	Model* model_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	
	// 補間レート
	float interpolationRate;

	// 終了フラグ
	bool isFinished_ = false;
	
};