#include "GameStart.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <numbers>
//初期化
void GameStart::Initiaize(Model* model, ViewProjection* viewProjection, uint32_t texture) { 
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	texture_ = texture;
	worldTransform_.Initialize();
	worldTransform_.rotation_.z = std::numbers::pi_v<float>; // z軸の角度を設定
	worldTransform_.rotation_.y = std::numbers::pi_v<float>; // y軸の角度を設定
	worldTransform_.translation_.y = -2.0f;
	worldTransform_.translation_.z = -41.0f;
}

void GameStart::Update() { worldTransform_.UpdateMatrix(); }

void GameStart::Draw() { model_->Draw(worldTransform_, *viewProjection_, texture_); }

