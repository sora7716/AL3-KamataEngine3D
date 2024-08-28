#include "PlayerBullet.h"
#include "Model.h"
#include "TextureManager.h"
#include <cassert>

// 初期化
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model); // NUllポインタチェック
	model_ = model;
	texture_ = TextureManager::Load("test/bullet.png"); // テクスチャの読み込み
	worldTransform_.Initialize();                       // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position;            // 引数で受け取った初期座標をセット
	velocity_ = velocity;                               // 引数で受け取った速度をメンバ変数に代入
}

// 更新
void PlayerBullet::Update() {
	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
	// 経過時間でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, texture_); }

// 衝突を検出したら呼び出されるコールバック関数
void PlayerBullet::OnCollision() { isDead_ = true; }

// デスフラグのゲッター
bool PlayerBullet::IsDead() const { return isDead_; }

// ワールドポジションのゲッター
Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

//AABBのゲッター
AABB PlayerBullet::GetAABB() {
	Vector3 worldPosition = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPosition.x - kWidth / 2.0f, worldPosition.y - kHeight / 2.0f, worldPosition.z - kDepth / 2.0f};
	aabb.max = {worldPosition.x + kWidth / 2.0f, worldPosition.y + kHeight / 2.0f, worldPosition.z + kDepth / 2.0f};
	return aabb;
}
