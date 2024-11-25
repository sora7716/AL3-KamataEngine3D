#include "PlayerModel.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include <cassert>
#include <string>

#pragma region インターフェース
// デバックテキスト
void IPlayerModel::DebugText(const char* label) {
	(void)label;
#ifdef _DEBUG
	std::string imGuiLabel = (std::string)label + ".size";
	ImGui::DragFloat3(imGuiLabel.c_str(), &worldTransform_.scale_.x, 0.1f, 0.0f, 3.0f);
	imGuiLabel = (std::string)label + ".rotate";
	ImGui::DragFloat3(imGuiLabel.c_str(), &worldTransform_.rotation_.x, 0.1f);
	imGuiLabel = (std::string)label + ".translate";
	ImGui::DragFloat3(imGuiLabel.c_str(), &worldTransform_.translation_.x, 0.1f);
#endif // DEBUG
}

// 親子付け
void IPlayerModel::SetParent(const WorldTransform *parent) { worldTransform_.parent_ = parent; }

// ワールドトランスフォームのゲッター
const WorldTransform& IPlayerModel::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}
#pragma endregion

#pragma region 頭
// 初期化
void Head::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransform_.rotation_ = {pi_f / 2.0f, 0.0f, pi_f};
}

// 更新
void Head::Update() { worldTransform_.UpdateMatrix(); }

// デバックテキスト
void Head::DebugText() { IPlayerModel::DebugText("head"); }

// 描画
void Head::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma region 体
// 初期化
void Body::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.2f, 0.0f};
}

// 更新
void Body::Update() { worldTransform_.UpdateMatrix(); }

// デバックテキスト
void Body::DebugText() { IPlayerModel::DebugText("body"); }

// 描画
void Body::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma region 右腕
// 初期化
void RightArm::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.5f, 1.2f, 0.0f};
}

// 更新
void RightArm::Update() { worldTransform_.UpdateMatrix(); }

// デバックテキスト
void RightArm::DebugText() { IPlayerModel::DebugText("rightArm"); }

// 描画
void RightArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma region 左腕
// 初期化
void LeftArm::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {-0.5f, 1.2f, 0.0f};
}

// 更新
void LeftArm::Update() { worldTransform_.UpdateMatrix(); }

// デバックテキスト
void LeftArm::DebugText() { IPlayerModel::DebugText("leftArm"); }

// 描画
void LeftArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma region プレイヤーのモデル
// 初期化
void PlayerModel::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	// 配列の大きさを設定
	iPlayerModels_.resize(4);
	// 生成
	iPlayerModels_[(int)Parts::kHead] = new Head();
	iPlayerModels_[(int)Parts::kBody] = new Body();
	iPlayerModels_[(int)Parts::kRightArm] = new RightArm();
	iPlayerModels_[(int)Parts::kLeftArm] = new LeftArm();
	// 初期化
	for (int i = 0; i < 4; i++) {
		assert(models[i]);
		iPlayerModels_[i]->Initialize(models[i].get(), viewProjection);
	}
}
// 更新
void PlayerModel::Update() {
	for (auto iPalayerModel : iPlayerModels_) {
		iPalayerModel->Update();
#ifdef _DEBUG
		ImGui::Begin("playerParts");
		iPalayerModel->DebugText();
		ImGui::End();
#endif // _DEBUG
	}
}

// 描画
void PlayerModel::Draw() {
	for (auto iPalayerModel : iPlayerModels_) {
		iPalayerModel->Draw();
	}
}

// 親のセッター
void PlayerModel::SetParent(const WorldTransform* parent) {
	// 体->Parent
	iPlayerModels_[(int)Parts::kBody]->SetParent(parent);
	// 頭->体
	iPlayerModels_[(int)Parts::kHead]->SetParent(&iPlayerModels_[(int)Parts::kBody]->GetWorldTransform());
	// 右腕->体
	iPlayerModels_[(int)Parts::kRightArm]->SetParent(&iPlayerModels_[(int)Parts::kBody]->GetWorldTransform());
	// 左腕->体
	iPlayerModels_[(int)Parts::kLeftArm]->SetParent(&iPlayerModels_[(int)Parts::kBody]->GetWorldTransform());
}

#pragma endregion
