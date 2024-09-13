#include "SelectButton.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/scene/title/select/Select.h"
#include "input/Input.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include <cassert>


// 初期化
void StartButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                         // Nullチェック
	model_ = model;                        // モデルを受け取る
	viewProjection_ = viewProjection;      // ビュープロジェクションを受け取る
	worldTransform_.Initialize();          // ワールドトランスフォームの初期化
	worldTransform_.translation_.z = 0.6f; // z座標を設定
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

// 初期化
void StartBackButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                                        // Nullチェック
	model_ = model;                                       // モデルを受け取る
	viewProjection_ = viewProjection;                     // ビュープロジェクションを受け取る
	worldTransform_.Initialize();                         // ワールドトランスフォームの初期化
	worldTransform_.translation_ = {-10.0f, 1.2f, 10.0f}; // 座標の設定
	positionY_ = worldTransform_.translation_.y;          // Y座標設定
}

// 更新
void StartBackButton::Update() {
#ifdef _DEBUG
	ImGui::Begin("startBack");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
	// ボタンの線形補間
	ButtonLerp();
	if (isSelectChangeColor_) {
		Animation();
	} else {
		worldTransform_.translation_.y = positionY_;
	}
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void StartBackButton::Draw() {
	if (!isSelectChangeColor_) {
		model_->Draw(worldTransform_, *viewProjection_);
	} else {
		model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	}
}

// 選択時のアニメーション
void StartBackButton::Animation() {
	static float width = 0.2f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + positionY_;
	theta += 1.0f / 5.0f;
}

// 初期化
void RuleBackButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                                         // Nullチェック
	model_ = model;                                        // モデルを受け取る
	viewProjection_ = viewProjection;                      // ビュープロジェクションを受け取る
	worldTransform_.Initialize();                          // ワールドトランスフォームの初期化
	worldTransform_.translation_ = {-10.0f, -1.5f, 10.0f}; // 座標の設定
	positionY_ = worldTransform_.translation_.y;           // Y座標設定
}

// 更新
void RuleBackButton::Update() {
#ifdef _DEBUG
	ImGui::Begin("ruleBack");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
	if (isSelectChangeColor_) {
		Animation();
	} else {
		worldTransform_.translation_.y = positionY_;
	}
	// ボタンの線形補間
	ButtonLerp();
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void RuleBackButton::Draw() {
	if (!isSelectChangeColor_) {
		model_->Draw(worldTransform_, *viewProjection_);
	} else {
		model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	}
}
// 選択時のアニメーション
void RuleBackButton::Animation() {
	static float width = 0.2f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + positionY_;
	theta += 1.0f / 5.0f;
}

// 初期化
void RuleButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                                           // Nullチェック
	model_ = model;                                          // モデルを受け取る
	viewProjection_ = viewProjection;                        // ビュープロジェクションを受け取る
	worldTransform_.Initialize();                            // ワールドトランスフォームの初期化
	worldTransform_.translation_.z = 0.6f;                   // z座標を設定
	worldTransform_.rotation_.y = std::numbers::pi_v<float>; // y座標の角度を設定
}

// 更新
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

// 描画
void RuleButton::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// 初期化
void SelectButton::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                    // Nullチェック
	model_ = model;                   // モデルを受け取る
	viewProjection_ = viewProjection; // ビュープロジェクションを受け取る
	worldTransform_.Initialize();     // ワールドトランスフォームの初期化
	worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_.translation_.z = 10.0f;
	worldTransform_.translation_.x = -3.2f;
	positionY = 1.0f;
}

// 更新
void SelectButton::Update() {
	if (isButtonLerp_ && frame_ >= Select::kEndFrame) {
		if (Input::GetInstance()->TriggerKey(DIK_W)) {
			positionY = 1.0f; // ゲームスタートを選択
		} else if (Input::GetInstance()->TriggerKey(DIK_S)) {
			positionY = -1.5f; // ゲームルールを選択1
		}
		if (positionY >= 1.0f) { // ゲームスタートを選択したときに色を変更
			isSelectStart_ = true;
			isSelectRule_ = false;
		} else if (positionY <= -1.5f) { // ゲームルールを選択したときに色を変更
			isSelectStart_ = false;
			isSelectRule_ = true;
		}
		if (isSelectStart_ && Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isGameStart_ = true; // ゲームスタートをクリックしたとき
		}
		if (isSelectRule_ && Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isGameRule_ = true; // ゲームルールをクリックしたとき
		}
	} else {
		isGameStart_ = false;
		isGameRule_ = false;
	}
	

	worldTransform_.translation_.y = positionY;
	worldTransform_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("selectButton");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::Text("frame:%f", frame_);
	ImGui::Checkbox("isGameStartPress", &isGameStart_);
	ImGui::End();
#endif // _DEBUG
}

// 描画
void SelectButton::Draw() {}

#pragma region セレクトキー(W)の背景
void SelectKeyW_Back::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.4f, 0.4f, 0.4f};
	worldTransform_.rotation_.x = std::numbers::pi_v<float>;
	worldTransform_.translation_.x = -2.7f;
}

void SelectKeyW_Back::Update() {

#ifdef _DEBUG
	ImGui::Begin("KeyW_Back");
	ImGui::DragFloat3("tanslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void SelectKeyW_Back::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}

#pragma endregion

//=============================================================================================================================

#pragma region セレクトキー(W)の文字

void SelectKeyW_Moji::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {.6f, .6f, 0.6f};
	worldTransform_.rotation_.x = std::numbers::pi_v<float>;
	worldTransform_.translation_.z = .75f;
}

void SelectKeyW_Moji::Update() {

	#ifdef _DEBUG
	ImGui::Begin("KeyW_moji");
	ImGui::DragFloat3("tanslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void SelectKeyW_Moji::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion 

//=============================================================================================================================

#pragma region セレクトキー(S)の背景
void SelectKeyS_Back::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.4f, 0.4f, 0.4f};
	worldTransform_.rotation_.x = std::numbers::pi_v<float>;
	worldTransform_.translation_.x = -2.64f;
	worldTransform_.translation_.z = -.12f;
}

void SelectKeyS_Back::Update() {

	#ifdef _DEBUG
	ImGui::Begin("KeyS_Back");
	ImGui::DragFloat3("tanslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void SelectKeyS_Back::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

//=============================================================================================================================

#pragma region セレクトキー(S)の文字

void SelectKeyS_Moji::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {.8f, .8f, 0.8f};
	worldTransform_.translation_.z = .01f;
}

void SelectKeyS_Moji::Update() {

#ifdef _DEBUG
	ImGui::Begin("KeyS_moji");
	ImGui::DragFloat3("tanslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void SelectKeyS_Moji::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

//=============================================================================================================================

#pragma region セレクトキー(ESC)の背景
void SelectKeyESC_Back::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.4f, 0.4f, 0.4f};
	worldTransform_.rotation_.x = std::numbers::pi_v<float>;
	worldTransform_.translation_ = {-7.61f, 4.29f, 12.93f};
}

void SelectKeyESC_Back::Update() {

#ifdef _DEBUG
	ImGui::Begin("KeyESC_Back");
	ImGui::DragFloat3("tanslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void SelectKeyESC_Back::Draw() {
	if (phase_ == 0 || phase_ == 1) {
		//model_->Draw(worldTransform_, *viewProjection_);
	}
}

#pragma endregion

#pragma region セレクトキー(ESC)
void SelectKeyESC_Moji::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1, 1, 0.6f};
	worldTransform_.rotation_.x = std::numbers::pi_v<float>;
	worldTransform_.translation_ = {.64f, .18f, 1.49f};
	positionY_ = worldTransform_.translation_.y;
}

void SelectKeyESC_Moji::Update() {

#ifdef _DEBUG
	ImGui::Begin("KeyESC_Moji");
	ImGui::DragFloat3("tanslate", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	Animation();
	worldTransform_.UpdateMatrix();
}

void SelectKeyESC_Moji::Draw() { 

	if (phase_ == 0 || phase_ == 1) { 
		model_->Draw(worldTransform_, *viewProjection_); 
	}

}

void SelectKeyESC_Moji::Animation() {
	static float width = 0.1f;
	static float theta = 1.0f;
	worldTransform_.translation_.y = width * sin(theta) + positionY_;
	theta += 1.0f / 5.0f;
}
