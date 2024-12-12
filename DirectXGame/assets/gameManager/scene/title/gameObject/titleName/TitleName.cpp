#include "TitleName.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include <cassert>

// 初期化
void TitleName::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	models_.resize(models.size());
	for (int i = 0; i < models.size(); i++) {
		assert(models[i]);
		models_[i] = models[i].get();
	}
	viewProjection_ = viewProjection;
	const float position[5] = {-5.0f, -2.5f, 0.0f, 2.5f, 5.0f};
	for (int i = 0; i < models_.size(); i++) {
		WorldTransform* worldTransform = new WorldTransform;
		worldTransform->Initialize();
		worldTransform->scale_ = {2.0f, 2.0f, 2.0f};
		worldTransform->rotation_.y = pi_f / 2;
		worldTransform->translation_ = {position[i], 8.0f, -32.0f};
		worldTransforms_.push_back(worldTransform);
	}
}

// 更新
void TitleName::Update() {
	Animation();
	for (auto worldTransform : worldTransforms_) {
		worldTransform->UpdateMatrix();
	}
}

// 描画
void TitleName::Draw() {
	for (int i = 0; i < models_.size(); i++) {
		models_[i]->Draw(*worldTransforms_[i], *viewProjection_);
	}
}

void TitleName::Animation() {
	float endFrame = 200;

	if (frame_ <= endFrame) {
		frame_++;
	}

	for (auto worldTransform : worldTransforms_) {
		const float begin = worldTransform->translation_.y;
		const float end = 2.0f;

		worldTransform->translation_.y = Math::Lerp(begin, end, Easing::GetInstance()->InOutExpo(frame_ / endFrame));
	}
}
