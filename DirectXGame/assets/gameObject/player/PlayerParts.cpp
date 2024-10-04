#include "PlayerParts.h"
#include "numbers"


#pragma region プレイヤーパーツ(体)

void PlayerBody::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	size_ = {0.6f, 0.6f, 0.6f};
	angle_.y = std::numbers::pi_v<float>;
	position_ = {0.0f, 0.0f, 3.0f};

	viewProjection_ = viewprojection;
}

void PlayerBody::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Body");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

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
	position_.y = 0.6f; 

	viewProjection_ = viewprojection;
}

void PlayerHead::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Head");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerHead::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion 


///============================================================================================================================================

#pragma region 右側のパーツクラス

#pragma region プレイヤーパーツ(右上腕)

void PlayerRight_UpperArm::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
	position_ = {-0.176f, 0.094f, 0.0f};
}

void PlayerRight_UpperArm::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Right_UpperArm");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerRight_UpperArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

///============================================================================================================================================

#pragma region プレイヤーパーツ(右腕)

void PlayerRight_LowerArm::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	position_ = {-0.159f, -0.179f, 0.0f};
	viewProjection_ = viewprojection;
}

void PlayerRight_LowerArm::Update() {

	SetAffine();

#ifdef _DEBUG
	Begin("Right_Lower");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void PlayerRight_LowerArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion


///============================================================================================================================================

#pragma region プレイヤーパーツ(右もも)

void PlayerRight_Thigh::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	position_ = {-0.0989f, -0.347f, 0.0f};

	viewProjection_ = viewprojection;
}

void PlayerRight_Thigh::Update() {

	SetAffine();

#ifdef _DEBUG
	Begin("Right_thigh");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerRight_Thigh::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

///============================================================================================================================================

#pragma region プレイヤーパーツ(右足)

void PlayerRight_Leg::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	position_ = {0.009f, -0.1677f, 0.002f};

	viewProjection_ = viewprojection;
}

void PlayerRight_Leg::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Right_leg");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerRight_Leg::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma endregion

///============================================================================================================================================

#pragma region 左側のパーツクラス

#pragma region プレイヤーパーツ(左上腕)

void PlayerLeft_UpperArm::Initialize(Model* model, ViewProjection* viewprojection) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	viewProjection_ = viewprojection;
	position_ = {0.178f, 0.095f, 0.0f};
}

void PlayerLeft_UpperArm::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Left_UpperArm");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // DEBUG

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
	position_ = {0.157f, -0.181f, 0.0f};
	viewProjection_ = viewprojection;
}

void PlayerLeft_LowerArm::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Left_Lower");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG
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
	position_ = {0.1f, -0.34f, 0.002f};

	viewProjection_ = viewprojection;
}

void PlayerLeft_Thigh::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Left_thigh");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

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
	position_ = {-0.009f, -0.1677f, 0.002f};

	viewProjection_ = viewprojection;
}

void PlayerLeft_Leg::Update() {

	SetAffine();
#ifdef _DEBUG
	Begin("Left_leg");
	DragFloat3("scale", &size_.x, 0.01f);
	DragFloat3("rotate", &angle_.x, 0.01f);
	DragFloat3("translate", &position_.x, 0.01f);
	End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Leg::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma endregion