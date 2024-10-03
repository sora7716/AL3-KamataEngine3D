#include "Player.h"

void Player::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewProjection;

}

void Player::Update() {


	worldTransform_.UpdateMatrix();

}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }