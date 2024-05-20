#include"Player.h"
#include<cassert>

void Player::Initialize(Model* model,uint32_t texturehundle,ViewProjection *viewprojection) {
	assert(model_);
	model_ = model;
	texturehundle_ = texturehundle;
	viewprojection_ = viewprojection;



}

void Player::Update() { 
	worldtransform_.TransferMatrix();

}
void Player::Draw() { 
	model_->Draw(worldtransform_, *viewprojection_, texturehundle_);

}