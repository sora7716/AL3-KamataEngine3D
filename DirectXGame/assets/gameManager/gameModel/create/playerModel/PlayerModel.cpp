#include "PlayerModel.h"

#pragma region 頭
// 初期化
void Head::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
	worldTransform_.rotation_ = {pi_f / 2.0f, 0.0f, pi_f};
}

// 更新
void Head::Update() {IModel::Update(); }

// デバックテキスト
void Head::DebugText() { IModel::DebugText("head"); }

// 描画
void Head::Draw() { IModel::Draw(); }

#pragma endregion

#pragma region 体
// 初期化
void Body::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 0.2f, 0.0f};
	// アニメーションの初期化
	InitializeFloatingGimmick();
}

// 更新
void Body::Update() {
	worldTransform_.translation_.y = UpdateFloatingGimmick();
	IModel::Update();
}

// デバックテキスト
void Body::DebugText() { IModel::DebugText("body"); }

// 描画
void Body::Draw() { IModel::Draw(); }

#pragma endregion

#pragma region 右腕
// 初期化
void RightArm::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.5f, 1.2f, 0.0f};
	// アニメーションの初期化
	InitializeFloatingGimmick();
}

// 更新
void RightArm::Update() {
	// アニメーションの更新
	worldTransform_.rotation_.x = UpdateTriangleGimmick();
	IModel::Update();
}

// デバックテキスト
void RightArm::DebugText() { IModel::DebugText("rightArm"); }

// 描画
void RightArm::Draw() { IModel::Draw(); }

#pragma endregion

#pragma region 左腕
// 初期化
void LeftArm::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model,viewProjection);
	worldTransform_.translation_ = {-0.5f, 1.2f, 0.0f};
	// アニメーションの初期化
	InitializeFloatingGimmick();
}

// 更新
void LeftArm::Update() {
	// アニメーションの更新
	worldTransform_.rotation_.x = UpdateTriangleGimmick();
	IModel::Update();
}

// デバックテキスト
void LeftArm::DebugText() { IModel::DebugText("leftArm"); }

// 描画
void LeftArm::Draw() { IModel::Draw(); }

#pragma endregion

#pragma region プレイヤーのモデル
// 初期化
void PlayerModel::Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection) {
	// 配列の大きさを設定
	parts_.resize((int)Parts::kPartsNum);
	// 生成
	parts_[(int)Parts::kHead] = new Head();
	parts_[(int)Parts::kBody] = new Body();
	parts_[(int)Parts::kRightArm] = new RightArm();
	parts_[(int)Parts::kLeftArm] = new LeftArm();
	// 初期化
	for (int i = 0; i < (int)Parts::kPartsNum; i++) {
		assert(models[i]);
		parts_[i]->Initialize(models[i], viewProjection);
	}
}
// 更新
void PlayerModel::Update() {
	for (auto iPalayerModel : parts_) {
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
	for (auto iPalayerModel : parts_) {
		iPalayerModel->Draw();
	}
}

// 親のセッター
void PlayerModel::SetParent(const WorldTransform* parent) {
	// 体->Parent
	parts_[(int)Parts::kBody]->SetParent(parent);
	// 頭->体
	parts_[(int)Parts::kHead]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 右腕->体
	parts_[(int)Parts::kRightArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 左腕->体
	parts_[(int)Parts::kLeftArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
}

#pragma endregion
