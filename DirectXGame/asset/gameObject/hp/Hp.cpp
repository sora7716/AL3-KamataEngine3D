#include "Hp.h"
#include "Sprite.h"
#include "TextureManager.h"

void Hp::Initialize() {

	textureHandle_ = TextureManager::Load("hp/heart.png");

	worldTransform_.Initialize();
	worldTransform_.translation_.x = 1060.0f;
	worldTransform_.translation_.y = 650.0f;

	for (int i = 0; i < hpCount_; i++) {
		sprites_[i] = Sprite::Create(textureHandle_, {0, 0});
	}

}

void Hp::Update() {

	worldTransform_.UpdateMatrix();
}

void Hp::Draw() {

	for (int i = 0; i < hpCount_; i++) {
		sprites_[i]->SetPosition({worldTransform_.translation_.x + (i * 72), worldTransform_.translation_.y});
		sprites_[i]->Draw();
	}

}

int Hp::GetHpCount() { return this->hpCount_; } 

void Hp::SetHpCount(int count) { this->hpCount_ = count; }