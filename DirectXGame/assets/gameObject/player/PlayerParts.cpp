#include "PlayerParts.h"

#pragma region プレイヤーパーツ(体)

void PlayerBody::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
}

void PlayerBody::Update() {

	SetAffine();

	worldTransform_.UpdateMatrix();
}

void PlayerBody::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

///============================================================================================================================================

#pragma region プレイヤーパーツ(頭)

void PlayerHead::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
}

void PlayerHead::Update() {

	SetAffine();

	worldTransform_.UpdateMatrix();
}

void PlayerHead::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion 

///============================================================================================================================================

#pragma region プレイヤーパーツ(左上腕)

void PlayerLeft_UpperArm::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
}

void PlayerLeft_UpperArm::Update() {

	SetAffine();

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_UpperArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

///============================================================================================================================================

#pragma region プレイヤーパーツ(左腕)

void PlayerLeft_LowerArm::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
}

void PlayerLeft_LowerArm::Update() {

	SetAffine();

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_LowerArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

///============================================================================================================================================

#pragma region プレイヤーパーツ(左もも)

void PlayerLeft_Thigh::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
}

void PlayerLeft_Thigh::Update() {

	SetAffine();

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Thigh::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

///============================================================================================================================================

#pragma region プレイヤーパーツ(左足)

void PlayerLeft_Leg::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
}

void PlayerLeft_Leg::Update() {

	SetAffine();

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Leg::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion