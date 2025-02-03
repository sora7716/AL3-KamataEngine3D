#include "PlayerModel.h"
#include "assets/gameManager/gameModel/create/staffModel/StaffModel.h"

#pragma region プレイヤーのモデルインターフェース

#pragma endregion

#pragma region 髪
// 初期化
void Hair::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	//worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
}

// 更新
void Hair::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Hair::DebugText() { IModel::DebugText("hair"); }

// 描画
void Hair::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 眉毛
// 初期化
void EyeBrows::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	//worldTransform_.translation_ = {0.0f, 0.2f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void EyeBrows::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
// 描画
void EyeBrows::Draw() { IModel::Draw(); }

// デバックテキスト
void EyeBrows::DebugText() { IModel::DebugText("eyeBrows"); }

#pragma endregion

#pragma region 顔
// 初期化
void Face::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	//worldTransform_.translation_ = {0.5f, 1.2f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void Face::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Face::DebugText() { IModel::DebugText("face"); }

// 描画
void Face::Draw() { IModel::Draw(); }

#pragma endregion

#pragma region 体
// 初期化
void Body::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_.y = pi_f;
	worldTransform_.translation_ = {-0.5f, -1.6f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void Body::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Body::DebugText() { IModel::DebugText("body"); }

// 描画
void Body::Draw() { IModel::Draw(); }

#pragma endregion

#pragma region 左腕
void LeftArm::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LeftArm::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LeftArm::DebugText() { IModel::DebugText("leftArm"); }
void LeftArm::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 右腕
void RightArm::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void RightArm::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void RightArm::DebugText() { IModel::DebugText("rightArm"); }
void RightArm::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 左腿
void LeftLeg::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LeftLeg::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LeftLeg::DebugText() { IModel::DebugText("leftLeg"); }
void LeftLeg::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 左脛
void LeftThigh::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LeftThigh::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LeftThigh::DebugText() { IModel::DebugText("leftThigh"); }
void LeftThigh::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 右腿
void RightLeg::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void RightLeg::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void RightLeg::DebugText() { IModel::DebugText("rightLeg"); }
void RightLeg::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 右脛
void RightThigh::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void RightThigh::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void RightThigh::DebugText() { IModel::DebugText("rightThigh"); }
void RightThigh::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 服(上)
void UpperClothing::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void UpperClothing::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void UpperClothing::DebugText() { IModel::DebugText("upperClothing"); }
void UpperClothing::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 服(下)
void LowerClothing::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LowerClothing::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LowerClothing::DebugText() { IModel::DebugText("lowerClothing"); }
void LowerClothing::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region プレイヤーのモデル
// デストラクタ
PlayerModel::~PlayerModel() {
	for (auto part : parts_) {
		delete part;
	}
	parts_.clear();
}
// 初期化
void PlayerModel::Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection) {
	// 配列の大きさを設定
	parts_.resize((int)Parts::kPartsNum);
	// 生成
	parts_[(int)Parts::kHair] = new Hair();
	parts_[(int)Parts::kEyeBrows] = new EyeBrows();
	parts_[(int)Parts::kFace] = new Face();
	parts_[(int)Parts::kBody] = new Body();
	parts_[(int)Parts::kLeftArm] = new LeftArm();
	parts_[(int)Parts::kRightArm] = new RightArm();
	parts_[(int)Parts::kLeftLeg] = new LeftLeg();
	parts_[(int)Parts::kLeftThigh] = new LeftThigh();
	parts_[(int)Parts::kRightLeg] = new RightLeg();
	parts_[(int)Parts::kRightThigh] = new RightThigh();
	parts_[(int)Parts::kUpperClothing] = new UpperClothing();
	parts_[(int)Parts::kLowerClothing] = new LowerClothing();
	parts_[(int)Parts::kStaff] = new StaffModel();
	// 初期化
	worldTransform_.Initialize();
	// 初期化
	for (int i = 0; i < (int)Parts::kPartsNum; i++) {
		assert(models[i]);
		parts_[i]->Initialize(models[i], viewProjection);
	}
}
// 更新
void PlayerModel::Update() {
	worldTransform_.UpdateMatrix();
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
	worldTransform_.parent_ = parent;
	//体<-Parent
	parts_[(int)Parts::kBody]->SetParent(&worldTransform_);
	//顔<-体
	parts_[(int)Parts::kFace]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//眉毛<-顔
	parts_[(int)Parts::kEyeBrows]->SetParent(&parts_[(int)Parts::kFace]->GetWorldTransform());
	//髪<-顔
	parts_[(int)Parts::kHair]->SetParent(&parts_[(int)Parts::kFace]->GetWorldTransform());
	//左腕<-体
	parts_[(int)Parts::kLeftArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//右腕<-体
	parts_[(int)Parts::kRightArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//左腿<-体
	parts_[(int)Parts::kLeftLeg]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//左脛<-左腿
	parts_[(int)Parts::kLeftThigh]->SetParent(&parts_[(int)Parts::kLeftLeg]->GetWorldTransform());
	// 右腿<-体
	parts_[(int)Parts::kRightLeg]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 右脛<-右腿
	parts_[(int)Parts::kRightThigh]->SetParent(&parts_[(int)Parts::kRightLeg]->GetWorldTransform());
	// 服上<-体
	parts_[(int)Parts::kUpperClothing]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 服下<-服上
	parts_[(int)Parts::kLowerClothing]->SetParent(&parts_[(int)Parts::kUpperClothing]->GetWorldTransform());
	// 武器<-左腕
	parts_[(int)Parts::kStaff]->SetParent(&parts_[(int)Parts::kLeftArm]->GetWorldTransform());
}
#pragma endregion
