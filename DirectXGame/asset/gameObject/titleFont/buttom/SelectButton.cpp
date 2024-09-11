#include "SelectButton.h"
#include "Model.h"
#include "ViewProjection.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include <cassert>

// 初期化
void StartButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                    // Nullチェック
	model_ = model;                   // モデルを受け取る
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	worldTransform_.translation_.z = 0.6f;//z座標を設定
}

// 更新
void StartButton::Update() {
#ifdef _DEBUG
	ImGui::Begin("start");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void StartButton::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

//初期化
void StartBackButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                    // Nullチェック
	model_ = model;                   // モデルを受け取る
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	worldTransform_.Initialize();     // ワールドトランスフォームの初期化
	worldTransform_.translation_ = {-10.0f, 1.2f, 10.0f};//座標の設定
}

//更新
void StartBackButton::Update() {
#ifdef _DEBUG
	ImGui::Begin("startBack");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
	//ボタンの線形補間
	ButtonLerp();
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

//描画
void StartBackButton::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

//初期化
void RuleBackButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                                       // Nullチェック
	model_ = model;                                      // モデルを受け取る
	viewProjection_ = viewProjection;                    // ビュープロジェクションを受け取る
	worldTransform_.Initialize();                        // ワールドトランスフォームの初期化
	worldTransform_.translation_ = {-10.0f, -1.5f, 10.0f}; // 座標の設定
}

//更新
void RuleBackButton::Update() {
#ifdef _DEBUG
	ImGui::Begin("ruleBack");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
	// ボタンの線形補間
	ButtonLerp();
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

//描画
void RuleBackButton::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

//初期化
void RuleButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                         // Nullチェック
	model_ = model;                        // モデルを受け取る
	viewProjection_ = viewProjection;      // ビュープロジェクションを受け取る
	worldTransform_.Initialize();          // ワールドトランスフォームの初期化
	worldTransform_.translation_.z = 0.6f; // z座標を設定
	worldTransform_.rotation_.y = std::numbers::pi_v<float>; //y座標の角度を設定
}

//更新
void RuleButton::Update() {
#ifdef _DEBUG
	ImGui::Begin("rule");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

//描画
void RuleButton::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
