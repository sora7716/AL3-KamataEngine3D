#pragma once
#include "assets/math/collision/Collider.h"
#include "assets/math/Math.h"
#include "assets/gameObject/effect/HitEffect.h"
#include "assets/math/ContactRecord.h"

//ハンマー(コライダークラスを継承)
class Hammer : public Collider,Math {

public:
	//コンストラクタ
	Hammer() = default;
	//デストラクタ
	~Hammer() override = default;
	//初期化
	void Initialize(Model* model, ViewProjection* viewProjection);
	//更新
	void Update();
	//描画
	void Draw();
	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision([[maybe_unused]] Collider* other) override;
	// 接触履歴を抹消
	void ClearContactRecord();
	//中心座標を取得
	Vector3 GetCenterPosition() const override;
	//角度のGetter
	const Vector3& GetRotation() const;
	// 倍率のSetter
	void SetScale(const Vector3& scale);
	// 角度のSetter
	void SetRotation(const Vector3& rotation);
	//親子関係を結ぶ
	void SetParent(const WorldTransform* parent);


private:

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform worldTransform_;
	// ヒットエフェクト
	std::unique_ptr<Model> modelHitEffect_ = nullptr;
	std::unique_ptr<HitEffect> hitEffect_ = nullptr;

	ContactRecord contactRecord_;
};