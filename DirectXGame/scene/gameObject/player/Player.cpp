#include "Player.h"
#include <cassert>
#include <numbers>
//プレイヤーの初期化
void Player::Initialize(Model* model, const uint32_t &textureHandle, ViewProjection* viewProjection, const Vector3& position) { 

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	viewProjection_ = viewProjection;

}

//プレイヤーの更新処理
void Player::Update() {

	if (Input::GetInstance()->PushKey(DIK_RIGHT)|| Input::GetInstance()->PushKey(DIK_LEFT)) {
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAttenuation;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.x -= kAttenuation;
		}
		velocity_ += acceleration;
	} else {
		float a = velocity_.GetVector().x;
		a *= (1 - kAttenuation);
		velocity_.SetVector({a, 0.0f, 0.0f});
		if (velocity_.GetVector().x * velocity_.GetVector().x < 0.001f) {
			velocity_.SetVector({0.0f, 0.0f, 0.0f});
		}
	}

    worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();
}

//プレイヤーの描画処理
void Player::Draw() { 

	model_->Draw(worldTransform_,*(viewProjection_),textureHandle_); 

}