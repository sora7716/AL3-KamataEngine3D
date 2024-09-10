#include "EnemyParent.h"

// 初期化
void EnemyParent::Initialize() {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

// 更新
void EnemyParent::Update() {
	worldTransform_.translation_.z -= 0.1f;
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
