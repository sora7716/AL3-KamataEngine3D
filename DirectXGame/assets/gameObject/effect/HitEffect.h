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
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	//更新
	void Update();
	//描画
	void Draw();

	

private://メンバ変数

	//モデルデータ
	Model* model_ = nullptr;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	static inline const int32_t kNumParticle = 8;
	std::array<WorldTransform, kNumParticle> worldTransforms_;
	//存続時間(消滅までの時間)<秒>
	static inline const float kDuration = 0.4f;
	//移動の速さ
	static inline const float kSpeed = 0.07f;
	// 分割した一個分の角度
	static inline const float kAngleUnit = (2 * pi_f) / kNumParticle;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;
	//色変更オブジェクト
	ObjectColor objectColor_;
	//色の数値
	Vector4 color_;
};