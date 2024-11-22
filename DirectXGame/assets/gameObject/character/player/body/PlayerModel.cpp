#include "PlayerModel.h"
#include "Model.h"
#include "ViewProjection.h"
#include "imgui.h"
#include <cassert>

// 親子付け
void IPlayerModel::SetParent(WorldTransform* parent) { worldTransform_.parent_ = parent; }


#pragma region 頭
// 初期化
void Head::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

// 更新
void Head::Update() { worldTransform_.UpdateMatrix(); }

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
}

// 更新
void Body::Update() { worldTransform_.UpdateMatrix(); }

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
}

// 更新
void RightArm::Update() { worldTransform_.UpdateMatrix(); }

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
}

// 更新
void LeftArm::Update() { worldTransform_.UpdateMatrix(); }

// 描画
void LeftArm::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

#pragma endregion

#pragma region プレイヤーのモデル
//初期化
void PlayerModel::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	//配列の大きさを設定
	iPlayerModels_.resize(4);
	//生成
	iPlayerModels_[0] = new Head();
	iPlayerModels_[1] = new Body();
	iPlayerModels_[2] = new RightArm();
	iPlayerModels_[3] = new LeftArm();
	//初期化
	for (int i = 0; i < 4; i++) {
		assert(models[i]);
		iPlayerModels_[i]->Initialize(models[i].get(), viewProjection);
	}
}
//更新
void PlayerModel::Update() {
	for (auto iPalayerModel : iPlayerModels_) {
		iPalayerModel->Update();
	}
}

//描画
void PlayerModel::Draw() {
	for (auto iPalayerModel : iPlayerModels_) {
		iPalayerModel->Draw();
	}
}

//親のセッター
void PlayerModel::SetParent(WorldTransform* parent) {
	for (auto iPlayerModel : iPlayerModels_) {
		iPlayerModel->SetParent(parent);
	}
}

#pragma endregion
