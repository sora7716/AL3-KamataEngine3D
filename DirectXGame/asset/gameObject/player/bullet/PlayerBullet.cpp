#include "PlayerBullet.h"
#include "Model.h"
#include "TextureManager.h"
#include <cassert>

// 初期化
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model); // NUllポインタチェック
	model_ = model;
	texture_ = TextureManager::Load("bullet.png"); // テクスチャの読み込み
	worldTransform_.Initialize();                  // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position;       // 引数で受け取った初期座標をセット
	velocity_ = velocity;//引数で受け取った速度をメンバ変数に代入
}

// 更新
void PlayerBullet::Update() {
	//座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	//行列の更新
	worldTransform_.UpdateMatrix(); 
}

// 描画
void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, texture_); }

//デスフラグのゲッター
bool PlayerBullet::IsDead() const { return isDead_; }
