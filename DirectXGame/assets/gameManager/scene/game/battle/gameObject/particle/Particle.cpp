#include "Particle.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include <cassert>
#include <cstdlib>

// 初期化
void Particle::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	emission_.Initialize();
	for (int i = 0; i < kParticleNum; i++) {
		WorldTransform* worldTransform = new WorldTransform;
		worldTransform->Initialize();
		worldTransform->scale_ = { kParticleSize, kParticleSize, kParticleSize };
		worldTransform->translation_ = emission_.translation_;
		particle_.push_back(worldTransform);
	}
	speed_.resize(kParticleNum);
	speed_[0] = deltaTime;
	objectColor_.Initialize();
}

// 更新
void Particle::Update() {
	particle_[0]->translation_.y += speed_[0];
	particle_[0]->UpdateMatrix();
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
	emission_.UpdateMatrix();
}

void Particle::DebugText() {
#ifdef DEBUG
	ImGui::Begin("particle");
	ImGui::DragFloat3("scale", &emission_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &emission_.rotation_.x, 0.1f);
	ImGui::DragFloat3("transration", &emission_.translation_.x, 0.1f);
	ImGui::End();
#endif // DEBUG
}

// 描画
void Particle::Draw() {
	model_->Draw(emission_, *viewProjection_, &objectColor_); 
	model_->Draw(*particle_[0], *viewProjection_);
}
