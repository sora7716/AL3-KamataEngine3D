#include "DeathParticles.h"
#include "ViewProjection.h"
#include "cassert"
#include "asset/math/Math.h"

#pragma region 頭のデスパーティクルの定義

void HeadDeathParticles::Initialize(Model* model, ViewProjection* viewProjection,const Vector3& position) {

	assert(model);

	model_ = model;

	// ワールド変数の初期化
	for (auto& WorldTransform : worldTransforms_) {
		WorldTransform.Initialize();
		WorldTransform.translation_ = position;
	}

	viewProjection_ = viewProjection;

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};

}

void HeadDeathParticles::Update() {

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// ワールド変換の更新
	for (auto& WorldTransform : worldTransforms_) {
		WorldTransform.UpdateMatrix();
	}

	HeadDeathParticles::Move();

	HeadDeathParticles::SubtractAlpha();

}

void HeadDeathParticles::Draw() {

	if (isFinished_) {
		return;
	}

	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_,&objectColor_);
	}

}

void HeadDeathParticles::Move() {

	for (uint32_t i = 0; i < kNumParticles; i++) {

		// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};
		// 球面座標系に基づく角度の計算
		float theta = (2.0f * pi * (i % kNumParticlesTheta)) / kNumParticlesTheta;

		float phi = (-pi / 2.0f) + (pi * (i / kNumParticlesTheta)) / kNumParticlesPhi;

		Matrix4x4 rotateMatrixY = Math::MakeRotateYMatrix(theta);
		Matrix4x4 rotateMatrixZ = Math::MakeRotateZMatrix(phi);

		// 行列の積を使用して、各軸の回転行列を結合させる
		Matrix4x4 rotateMatrix = rotateMatrixZ * rotateMatrixY;

		velocity = Math::Transform(velocity, rotateMatrix);
		worldTransforms_[i].translation_ += velocity;
	}


}

void HeadDeathParticles::SubtractAlpha() {

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	color_.w = std::clamp(1.0f - (counter_ / kDuration), 0.0f, 1.0f);

	// 色変更オブジェクトに色に数値を設定する
	objectColor_.SetColor(color_);
	// 色変更オブジェクトをVRAMに転送
	objectColor_.TransferMatrix();


}

#pragma endregion

//=============================================================================================================================

#pragma region 体のデスパーティクルの定義

void BodyDeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);

	model_ = model;

	// ワールド変数の初期化
	for (auto& WorldTransform : worldTransforms_) {

		WorldTransform.Initialize();
		WorldTransform.translation_ = position;
	}

	viewProjection_ = viewProjection;

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};

}

void BodyDeathParticles::Update() {

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// ワールド変換の更新
	for (auto& WorldTransform : worldTransforms_) {
		WorldTransform.UpdateMatrix();
	}

	BodyDeathParticles::Move();

	BodyDeathParticles::SubtractAlpha();

}

void BodyDeathParticles::Draw() {

	if (isFinished_) {
		return;
	}

	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_,&objectColor_);
	}


}

void BodyDeathParticles::Move() {

	for (uint32_t i = 0; i < kNumParticles; i++) {

		// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0, 0};
		// 球面座標系に基づく角度の計算
		float theta = (2.0f * pi * (i % kNumParticlesTheta)) / kNumParticlesTheta;

		float phi = (-pi / 2.0f) + (pi * (i / kNumParticlesTheta)) / kNumParticlesPhi;

		Matrix4x4 rotateMatrixY = Math::MakeRotateYMatrix(theta);
		Matrix4x4 rotateMatrixZ = Math::MakeRotateZMatrix(phi);

		// 行列の積を使用して、各軸の回転行列を結合させる
		Matrix4x4 rotateMatrix = rotateMatrixZ * rotateMatrixY;

		velocity = Math::Transform(velocity, rotateMatrix);
		worldTransforms_[i].translation_ += velocity;
	}
}

void BodyDeathParticles::SubtractAlpha() {

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	color_.w = std::clamp(1.0f - (counter_ / kDuration), 0.0f, 1.0f);

	// 色変更オブジェクトに色に数値を設定する
	objectColor_.SetColor(color_);
	// 色変更オブジェクトをVRAMに転送
	objectColor_.TransferMatrix();
}

#pragma endregion
