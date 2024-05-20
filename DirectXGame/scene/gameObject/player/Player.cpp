#include "Player.h"
#include <cassert>
//プレイヤーの初期化
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) { 

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
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