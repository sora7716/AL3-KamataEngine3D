#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "vector"
#include "assets/math/collision/Collider.h"

/*ベースキャラクター*/
class BaseCharacter : public Collider{

public://メンバ関数

	//初期化
	virtual void Initialize(std::vector<Model*> models, ViewProjection*viewProjection);

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//中心座標取得
	virtual Vector3 GetCenterPosition() const override;

	//ワールド変換データgetter
    const std::vector<WorldTransform*> GetWorldTransform() { return worldTransforms_; };

	//ビュープロジェクションgetter
	const ViewProjection* GetViewProjection() { return viewProjection_; }
	
	//ビュープロジェクションsetter
	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection;}

protected:

	//モデルデータ配列
	std::vector<Model*> models_;

	//ワールド変換データ
	std::vector<WorldTransform*> worldTransforms_;

	//ビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

};

