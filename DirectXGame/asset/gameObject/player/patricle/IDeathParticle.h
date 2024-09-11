#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "vector"

class IDeathParticle {
	
public:

	//パーティクルの名前
	enum class Particle {
		kHead,
		kBody,

		kParticleNum
	};

	using ParticleName = Particle;
	static inline ParticleName head = Particle::kHead; 
	static inline ParticleName body = Particle::kBody;

	static inline const int particleNum = static_cast<int>(Particle::kParticleNum);

public:

	virtual ~IDeathParticle() = default;

	virtual void Initialize(Model *model,ViewProjection *viewProjection,const Vector3 &position) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Move() = 0;

	virtual void SubtractAlpha() = 0;

	void SetParent(const WorldTransform* parent) {
		for (int32_t i = 0; i < kNumParticles; i++) {
			worldTransforms_[i].parent_ = parent;
		}
	}

	bool GetIsFinished() const { return isFinished_; }

protected:

	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	static inline const uint32_t kNumParticles = 80;
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	static inline const uint32_t kNumParticlesTheta = static_cast<uint32_t>(sqrtf(kNumParticles));
	static inline const uint32_t kNumParticlesPhi = kNumParticles / kNumParticlesTheta;

	static inline const float kDuration = 2.0f;

	static inline const float kSpeed = 0.8f;
	static inline const float pi = 3.14f;
	static inline const float kAngleUnit = (2 * pi) / kNumParticles;
	bool isFinished_ = false;

	float counter_ = 0.0f;

	ObjectColor objectColor_;
	Vector4 color_;
};
