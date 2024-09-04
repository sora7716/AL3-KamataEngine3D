#include "Player.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"

void Player::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

}

void Player::Update() {

	worldTransform_.UpdateMatrix();

}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}
