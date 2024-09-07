#include "PlayerParts.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include "asset/math/Aithmetic.h"
#include <cassert>
#include <cmath>
#include <numbers>
using namespace std::numbers;

//=============================================================================================================

#pragma region 頭クラスの定義

/// 初期化
void PlayerHead::Initialize(Model* model, ViewProjection* viewProjection) {

	// NULLポインタチェック
	assert(model);

#pragma region メンバ変数に引数のデータを記録

	model_ = model; // モデル

	viewProjection_ = viewProjection; // ビュープロジェクション

#pragma endregion

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	angle_ = {0.0f, pi_v<float> / 2.0f, 0.0f};
	position_ = {0.0f, 1.0f, 0.0f};
}

/// 更新
void PlayerHead::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("head");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	Animation();
	// 行列を更新する
	worldTransform_.UpdateMatrix();
}

/// 描画
void PlayerHead::Draw() {

	// 3Dモデルを描画する
	model_->Draw(worldTransform_, *viewProjection_);
}

void PlayerHead::Animation() {
	static float width = 0.2f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + position_.y;
	theta += 1.0f / 15.0f;
}

#pragma endregion

//=============================================================================================================

#pragma region 体クラスの定義

void PlayerBody::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	position_ = {0.0f, -2.25f, 0.0f};
	angle_ = {0.0f, 0.0f, 0.0f};
}

void PlayerBody::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("body");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	Animation();
	worldTransform_.UpdateMatrix();
}

void PlayerBody::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void PlayerBody::Animation() {
	static float width = 0.2f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + position_.y;
	theta += 1.0f / 15.0f;
}

#pragma endregion

//=============================================================================================================

#pragma region 腕クラスの定義
void PlayerArm::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	size_ = {0.7f, 0.7f, 0.7f};
	angle_ = {0.0f, 0.0f, 0.0f};
	position_ = {0.0f, -0.98f, 0.0f};
}

void PlayerArm::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("arm");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif //  _DEBUG
	Animation();
	worldTransform_.UpdateMatrix();
}

void PlayerArm::Draw() {}

void PlayerArm::Animation() {
	static float width = 0.2f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + position_.y;
	worldTransform_.rotation_.z = width * sin(theta) + 0.91f;
	theta += 1.0f / 15.0f;
}

#pragma endregion

//=============================================================================================================

#pragma region 左腕クラスの定義

void PlayerLeft_Arm::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	angle_ = {0.0f, 0.0f, 2.3f};
	position_ = {0.0f, 0.0f, 2.5f};
}

void PlayerLeft_Arm::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("leftArm");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // DEBUG

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Arm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

//=============================================================================================================

#pragma region 右腕クラスの定義

void PlayerRight_Arm::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	angle_ = {0.0f, 0.0f, 2.3f};
	position_ = {0.0f, 0.0f, -2.5f};
}

void PlayerRight_Arm::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("rightArm");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void PlayerRight_Arm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

//=============================================================================================================

//=============================================================================================================

#pragma region 耳クラスの定義

void PlayerEar::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	angle_ = {};
	position_ = {};
}

void PlayerEar::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("ear");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void PlayerEar::Draw() {}

#pragma endregion

//=============================================================================================================

//=============================================================================================================

#pragma region 左耳クラスの定義

void PlayerLeft_Ear::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	angle_ = {};
	position_ = {};
}

void PlayerLeft_Ear::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("leftEar");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Ear::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

//=============================================================================================================

//=============================================================================================================

#pragma region 右耳クラスの定義

void PlayerRight_Ear::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	angle_ = {};
	position_ = {};
}

void PlayerRight_Ear::Update() {
	SetSRT(); // SRTのセッター
#ifdef _DEBUG
	ImGui::Begin("rightEar");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void PlayerRight_Ear::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

//=============================================================================================================