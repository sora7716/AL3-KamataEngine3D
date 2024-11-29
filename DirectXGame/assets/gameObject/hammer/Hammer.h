#pragma once
#include "assets/math/collision/Collider.h"
#include "assets/math/Math.h"
#include "assets/gameObject/effect/HitEffect.h"
#include "assets/math/ContactRecord.h"

/// <summary>
/// ハンマー(コライダークラスと数学クラスを継承する)
/// </summary>
class Hammer : public Collider,Math {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Hammer() = default;
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Hammer() override = default;
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"> モデルデータ </param>
	/// <param name="viewProjection"> ビュープロジェクション </param>
	void Initialize(Model* model, ViewProjection* viewProjection);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	/// <param name="other"> 他のコライダー </param>
	void OnCollision([[maybe_unused]] Collider* other) override;
	
	/// <summary>
	/// 接触履歴を抹消
	/// </summary>
	void ClearContactRecord();
	
	/// <summary>
	/// 中心座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetCenterPosition() const override;
	
	/// <summary>
	/// 角度のGetter
	/// </summary>
	/// <returns></returns>
	const Vector3& GetRotation() const;
	
	/// <summary>
	/// スケールSetter
	/// </summary>
	/// <param name="scale"> スケール </param>
	void SetScale(const Vector3& scale);

	/// <summary>
	/// RotateSetter
	/// </summary>
	/// <param name="radian"> 角度 </param>
	void SetRotation(const Vector3& radian);
	
	/// <summary>
	/// 親子関係を結ぶ
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent);


private: // メンバ変数

	// モデルデータ
	Model* model_ = nullptr;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	
	// ワールド変換データ
	WorldTransform worldTransform_;
	
	// 衝突エフェクト
	std::unique_ptr<Model> modelHitEffect_ = nullptr;
	std::list<std::unique_ptr<HitEffect>> hitEffects_;

	// 接触記録
	ContactRecord contactRecord_;
};