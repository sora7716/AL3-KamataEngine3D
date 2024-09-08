#include "Hp.h"
#include "Sprite.h"
#include "TextureManager.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG


void Hp::Initialize() {

	textureHandle_ = TextureManager::Load("hp/heart.png");

	worldTransform_.Initialize();
	worldTransform_.translation_.x = 1200.0f;
	worldTransform_.translation_.y = 650.0f;

	for (int i = 0; i < hpCount_; i++) {
		sprites_[i] = Sprite::Create(textureHandle_, {0, 0});
	}

}

void Hp::Update() {

	/*ImGui::Begin("hp");
	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();*/

	worldTransform_.UpdateMatrix();
}

void Hp::Draw() {

	for (int i = 0; i < hpCount_; i++) {
		sprites_[i]->SetPosition({worldTransform_.translation_.x - (i * 72), worldTransform_.translation_.y});
		sprites_[i]->Draw();
	}

}

int Hp::GetHpCount() { return this->hpCount_; } 

void Hp::SetHpCount(int count) { this->hpCount_ = count; }