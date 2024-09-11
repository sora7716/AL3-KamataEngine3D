#include "EnemyParent.h"
#include "asset/gameObject/skydome/SkyDome.h"

// 初期化
void EnemyParent::Initialize() {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

// 更新
void EnemyParent::Update() {
	worldTransform_.translation_.z -= skyDome_->GetVelocityZ();
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 親クラスのセット
void EnemyParent::SetParent(const WorldTransform* parent) {
	// 親のセット
	worldTransform_, parent = parent;
}

// ワールドトランスフォームのゲッター
WorldTransform& EnemyParent::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

//ポジションのセッター
void EnemyParent::SetPosition(Vector3 position) { worldTransform_.translation_ = position; }

//スカイドームの設定
void EnemyParent::SetSkyDome(SkyDome* skyDome) { skyDome_ = skyDome; }
