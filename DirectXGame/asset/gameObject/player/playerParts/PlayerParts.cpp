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

void PlayerHead::DrawDebugText() {

#ifdef _DEBUG
	ImGui::Text("\nhead");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

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

	Animation();
	worldTransform_.UpdateMatrix();
}

void PlayerBody::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void PlayerBody::DrawDebugText() {

#ifdef _DEBUG
	ImGui::Text("\nbody");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

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

	Animation();
	worldTransform_.UpdateMatrix();
}

void PlayerArm::Draw() {}

void PlayerArm::DrawDebugText() {

#ifdef _DEBUG
	ImGui::Text("\narm");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

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

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Arm::Draw() {
	if (parts_IsDead_ != false) {
		return;
	}
	model_->Draw(worldTransform_, *viewProjection_); 
}

void PlayerLeft_Arm::DrawDebugText() {

#ifdef _DEBUG
		ImGui::Text("\nleftArm");
		ImGui::DragFloat3("scale", &size_.x, 0.01f);
		ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
		ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

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

	worldTransform_.UpdateMatrix();
}

void PlayerRight_Arm::Draw() { 

	if (parts_IsDead_ != false) {
		return;
	}
	model_->Draw(worldTransform_, *viewProjection_);
	
}

void PlayerRight_Arm::DrawDebugText() {

#ifdef _DEBUG
		ImGui::Text("\nright_Arm");
		ImGui::DragFloat3("scale", &size_.x, 0.01f);
		ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
		ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

#pragma endregion

//=============================================================================================================

//=============================================================================================================

#pragma region 耳クラスの定義

void PlayerEar::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	angle_ = {1.0f,1.5f,0.0f};
	position_ = {0.0f,1.0f,0.0f};
}

void PlayerEar::Update() {
	SetSRT(); // SRTのセッター

	Animation();
	worldTransform_.UpdateMatrix();
}

void PlayerEar::Draw() {}

void PlayerEar::DrawDebugText() {

	#ifdef _DEBUG
	
		ImGui::Text("\near");
		ImGui::DragFloat3("scale", &size_.x, 0.01f);
		ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
		ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

void PlayerEar::Animation() {
	static float width = 0.2f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + position_.y;
	worldTransform_.rotation_.z = width * sin(theta) + 0.91f;
	theta += 1.0f / 15.0f;
}

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
	position_ = {-1.5f,0.0f,0.0f};
}

void PlayerLeft_Ear::Update() {
	SetSRT(); // SRTのセッター

	worldTransform_.UpdateMatrix();
}

void PlayerLeft_Ear::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void PlayerLeft_Ear::DrawDebugText() {

#ifdef _DEBUG
		ImGui::Text("\nleft_ear");
		ImGui::DragFloat3("scale", &size_.x, 0.01f);
		ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
		ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

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
	position_ = {1.5f,0.0f,0.0f};
}

void PlayerRight_Ear::Update() {
	SetSRT(); // SRTのセッター

	worldTransform_.UpdateMatrix();
}

void PlayerRight_Ear::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

void PlayerRight_Ear::DrawDebugText() {

#ifdef _DEBUG
	ImGui::Text("\nright_ear");
	ImGui::DragFloat3("scale", &size_.x, 0.01f);
	ImGui::DragFloat3("rotate", &angle_.x, 0.01f);
	ImGui::DragFloat3("translate", &position_.x, 0.01f);
#endif // _DEBUG

}

#pragma endregion

//=============================================================================================================