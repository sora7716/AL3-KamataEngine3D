#include "Particle.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include <cassert>
#include <cstdlib>
#include <ctime>

// 初期化
void Particle::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	emission_.Initialize();
	std::srand(uint32_t(time(nullptr)));
	for (int i = 0; i < kParticleNum; i++) {
		Sphere sphere = {};
		sphere.worldTransform = new WorldTransform;
		sphere.worldTransform->Initialize();
		sphere.worldTransform->scale_ = {kParticleSize, kParticleSize, kParticleSize};
		sphere.speed = 2.0f;
		sphere.objectColor.Initialize();
		sphere.color = Math::ColorCodeTransform("#17F598");
		sphere.isAlive = false;
		particles_.push_back(sphere);
	}
	objectColor_.Initialize();
}

// 更新
void Particle::Update() {
	ParticleUpdate();
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
	emission_.UpdateMatrix();
}

void Particle::DebugText() {
	ImGui::Begin("particle");
	ImGui::DragFloat3("scale", &emission_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &emission_.rotation_.x, 0.1f);
	ImGui::DragFloat3("transration", &emission_.translation_.x, 0.1f);
	ImGui::Text("colorAlpha:%f", particles_[0].color.w);
	ImGui::End();
}

// 描画
void Particle::Draw() {
	model_->Draw(emission_, *viewProjection_, &objectColor_);
	for (auto& particle : particles_) {
		if (particle.isAlive) {
			model_->Draw(*particle.worldTransform, *viewProjection_, &particle.objectColor);
		}
	}
}

// パーティクルの生成
void Particle::ParticleCreate() {
	for (auto& particle : particles_) {
		if (!particle.isAlive) {
			particle.color = Math::ColorCodeTransform("#17F598");
			particle.radius = float(std::rand() % 5 + 1);
			particle.angle = float(std::rand() % 360);
			particle.worldTransform->translation_ = {
			    emission_.translation_.x + particle.radius * std::cos(particle.angle),
			    emission_.translation_.y + particle.radius * std::sin(particle.angle),
			    emission_.translation_.z,
			};
			particle.isAlive = true;
			break;
		}
	}
}

// パーティクルを動かす
void Particle::ParticleMove() {
	for (auto& particle : particles_) {
		if (particle.isAlive) {
			particle.worldTransform->translation_.z += particle.speed * deltaTime;
			Blend(particle);
			particle.worldTransform->UpdateMatrix();
			particle.objectColor.TransferMatrix();
		}
	}
}

// パーティクルの更新
void Particle::ParticleUpdate() {
	// 生成
	ParticleCreate();
	// 動かす
	ParticleMove();
}

// ブレンド
void Particle::Blend(Sphere &particle) {
	particle.color.w -= 0.5f*deltaTime;
	particle.objectColor.SetColor(particle.color);
	if (particle.color.w <= 0.0f) {
		particle.isAlive = false;
	}
}