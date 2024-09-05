#include "PlayerParts.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

using namespace std::numbers;

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
	worldTransform_.translation_.y = 3.5f;
	worldTransform_.rotation_.y = pi_v<float> / 2.0f;
}

/// 更新
void PlayerHead::Update() {
	ImGui::Begin("head");
	ImGui::DragFloat3("head.translate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();

	// 行列を更新する
	worldTransform_.UpdateMatrix();
}

/// 描画
void PlayerHead::Draw() {

	// 3Dモデルを描画する
	model_->Draw(worldTransform_, *viewProjection_);
}

#pragma endregion 

//=============================================================================================================

#pragma region 体クラスの定義

void PlayerBody::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
}

void PlayerBody::Update() { worldTransform_.UpdateMatrix(); }

void PlayerBody::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion 

//=============================================================================================================

#pragma region 左腕クラスの定義

void PlayerLeft_Arm::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
}

void PlayerLeft_Arm::Update() { worldTransform_.UpdateMatrix(); }

void PlayerLeft_Arm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion 

//=============================================================================================================

#pragma region 右腕クラスの定義

void PlayerRight_Arm::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
}

void PlayerRight_Arm::Update() { worldTransform_.UpdateMatrix(); }

void PlayerRight_Arm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion