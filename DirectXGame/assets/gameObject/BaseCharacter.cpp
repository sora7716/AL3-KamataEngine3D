#include "BaseCharacter.h"

void BaseCharacter::Initialize(std::vector<Model*> models, ViewProjection* viewProjection) {

	//引数で受け取ったデータをメンバ変数に記録する
	models_ = models;
	viewProjection_ = viewProjection;

	//コライダーの初期化
	Collider::Initialize();
}

Vector3 BaseCharacter::GetCenterPosition() const {

	//ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransforms_[0]->matWorld_.m[3][0];
	worldPos.y = worldTransforms_[1]->matWorld_.m[3][1];
	worldPos.z = worldTransforms_[2]->matWorld_.m[3][2];

	return worldPos;
}
