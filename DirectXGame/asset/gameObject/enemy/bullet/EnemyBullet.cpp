#include "EnemyBullet.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "asset/math/Aithmetic.h"

// 初期化
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// モデルを代入
	model_ = model;
	// ワールドトランスフォームを初期化
	worldTransform_.Initialize();
	// 初期座標を上書き
	worldTransform_.translation_ = position;
	// 速度を設定
	velocity_ = velocity;
	texture_ = TextureManager::Load("test/enemyBullet.png");
}

// 更新
void EnemyBullet::Update() {

	//経過時間でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 速度分トランスレイションに加算
	worldTransform_.translation_ += velocity_;
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	// 弾
	model_->Draw(worldTransform_, viewProjection, texture_);
}

//デスフラグのゲッター
bool EnemyBullet::IsDead() const { return isDead_; }
