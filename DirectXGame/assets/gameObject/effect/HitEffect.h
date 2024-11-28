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

public:

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

	void DrawDebugText();

private://メンバ変数

	//モデルデータ
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
	//終了フラグ
	bool isFinished_;
	
	float alphaEase_;
};