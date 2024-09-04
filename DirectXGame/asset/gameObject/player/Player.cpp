#include "Player.h"
#include <cassert>
#include "Model.h"
#include "ViewProjection.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

//初期化
void Player::Initialize(Model* model, ViewProjection* viewProjection) { 
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;
}

//更新
void Player::Update() { 
	ImGui::Begin("player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
	worldTransform_.UpdateMatrix(); 
}

//描画
void Player::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_); // プレイヤー
}

//親子関係を作る
void Player::SetPearent(const WorldTransform* parent) { 
	worldTransform_.parent_ = parent; 
}
