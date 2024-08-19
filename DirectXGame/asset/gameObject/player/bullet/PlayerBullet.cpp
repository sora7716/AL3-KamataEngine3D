#include "PlayerBullet.h"
#include "Model.h"
#include "TextureManager.h"
#include <cassert>

// 初期化
void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	assert(model); // NUllポインタチェック
	model_ = model;
	texture_ = TextureManager::Load("bullet.png"); // テクスチャの読み込み
	worldTransform_.Initialize();                  // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position;       // 引数で受け取った初期座標をセット
}

// 更新
void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix(); 
}

// 描画
void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, texture_); }
