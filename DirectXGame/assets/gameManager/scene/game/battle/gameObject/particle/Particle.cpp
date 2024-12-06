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
	emission_.translation_.z = -1.0f;
	std::srand(uint32_t(time(nullptr)));
	for (int i = 0; i < kParticleNum; i++) {
		Sphere sphere = {};
		sphere.worldTransform = new WorldTransform;
		sphere.worldTransform->Initialize();
		sphere.worldTransform->scale_ = {kParticleSize, kParticleSize, kParticleSize};
		sphere.objectColor.Initialize();
		sphere.color = Math::ColorCodeTransform("#17F598");
		sphere.isAlive = false;
		particles_.push_back(sphere);
	}
}

// 更新
void Particle::Update() {
	ParticleUpdate();
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
	for (auto& particle : particles_) {
		if (particle.isAlive) {
			model_->Draw(*particle.worldTransform, *viewProjection_, &particle.objectColor);
		}
	}
}

// 飛ぶ方向のセッター
void Particle::SetMove(Vector3 move) { move_ = move; }

//親子付け
void Particle::SetParent(WorldTransform* parent) { emission_.parent_ = parent; }

//カメラの向いている方向のセッター
void Particle::SetDirectionView(ViewProjection* viewProjection) { directionViewProjection_ = viewProjection; }

// パーティクルの生成
void Particle::ParticleCreate() {
	for (auto& particle : particles_) {
		if (!particle.isAlive) {
			direction_.z = 1.0f;
			// 移動量に速さを反映
			direction_ = Math::Normalize(direction_) * kParticleSpeed_;
			Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
			direction_ = Math::TransformNormal(direction_, rotMat);
			particle.color = BLACK;
			particle.radius = (float)rand() / (float)RAND_MAX * 0.3f;
			particle.angle = float(std::rand() % 360);
			particle.worldTransform->translation_ = {
			    particle.radius * std::cos(radian(particle.angle)),
			    particle.radius * std::sin(radian(particle.angle)),
			    1.0f,
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
			particle.worldTransform->translation_ += Math::Normalize(move_) * kParticleSpeed_ * deltaTime;
			Blend(particle);
			particle.worldTransform->parent_ = &emission_;
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
void Particle::Blend(Sphere& particle) {
	particle.color.w -= deltaTime / kParticleLifeTime_;
	particle.objectColor.SetColor(particle.color);
	if (particle.color.w <= 0.0f) {
		particle.isAlive = false;
	}
}