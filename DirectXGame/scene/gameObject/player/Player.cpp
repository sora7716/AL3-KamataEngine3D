#include "Player.h"
#include <cassert>
//プレイヤーの初期化
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) { 

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;

}

//プレイヤーの更新処理
void Player::Update() {

	worldTransform_.TransferMatrix();

}

//プレイヤーの描画処理
void Player::Draw() { 

	model_->Draw(worldTransform_,*(viewProjection_),textureHandle_); 

}