#include "EnemyBullet.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "asset/gameObject/enemy/Enemy.h"
#include "asset/gameObject/player/Player.h"
#include "asset/math/Math.h"

// 初期化
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// モデルを代入
	model_ = model;
	// ワールドトランスフォームを初期化
	worldTransform_.Initialize();
	// 初期座標を上書き
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.5f, 0.5f, 3.0f};

	// 速度を設定
	velocity_ = velocity;
	texture_ = TextureManager::Load("test/enemyBullet.png");

	// 弾の向き
	Direction();
}

// 更新
void EnemyBullet::Update() {

	// 経過時間でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	// 速度分トランスレイションに加算
	worldTransform_.translation_ += velocity_;

	// 追跡
	Tracking();

	// 弾の向き
	Direction();

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	// 弾
	model_->Draw(worldTransform_, viewProjection, texture_);
}

// 衝突を検出したら呼び出されるコールバック関数
void EnemyBullet::OnCollision() { isDead_ = true; }

// デスフラグのゲッター
bool EnemyBullet::IsDead() const { return isDead_; }

// プレイヤーのセッター
void EnemyBullet::SetPlayer(Player* player) { player_ = player; }

//ワールドポジションのゲッター
Vector3 EnemyBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

//AABBのゲッター
AABB EnemyBullet::GetAABB() {
	Vector3 worldPosition = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPosition.x - kWidth / 2.0f, worldPosition.y - kHeight / 2.0f, worldPosition.z - kDepth / 2.0f};
	aabb.max = {worldPosition.x + kWidth / 2.0f, worldPosition.y + kHeight / 2.0f, worldPosition.z + kDepth / 2.0f};
	return aabb;
}

// 追跡する弾
void EnemyBullet::Tracking() {
	// 媒介変数を加算(0～1)
	if (t < 1.0f) {
		t += 0.1f / 60.0f;
	} else {
		t = 1.0f;
	}

	// ワールド座標
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	// 敵弾から自キャラへのベクトルを計算
	Vector3 toPlayer = player_->GetWorldPosition() - worldPos;
	// ベクトルを正規化する
	toPlayer = Math::Normalize(toPlayer);
	velocity_ = Math::Normalize(velocity_);
	// 球面線形補間により、今の速度と自キャラへのベクトルを内挿し、新たな速度とする
	velocity_ = Math::SLerp(velocity_, toPlayer, t) * Enemy::kBulletSpeed;
}

// 弾の向き
void EnemyBullet::Direction() {
	// Y軸周りの角度(θy)
	worldTransform_.rotation_.y = atan2(velocity_.x, velocity_.z);
	float velocityXZ = Math::Length({velocity_.x, 0.0f, velocity_.z});
	// X軸周りの角度(θx)
	worldTransform_.rotation_.x = atan2(-velocity_.y, velocityXZ);
}
