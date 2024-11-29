#include "MimicModel.h"
#include "assets/math/collision/Collision.h"

#pragma region 蓋
// 初期化
void Lid::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	IModel::InitializeAnimation();
	startAngle_ = -45.0f;
	endAngle_ = 40.0f;
}

// 更新
void Lid::Update() {
	worldTransform_.rotation_.x = IModel::LerpAnimation(EasingMode::kOutQuad);
	IModel::Update();
}

// デバックテキスト
void Lid::DebugText() { IModel::DebugText("Lid"); }

// 描画
void Lid::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 目
// 初期化
void Eye::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void Eye::Update() { IModel::Update(); }

// デバックテキスト
void Eye::DebugText() { IModel::DebugText("eye"); }

// 描画
void Eye::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 箱
// 初期化
void Box::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	IModel::InitializeAnimation();
	startAngle_ = 15.0f;
	endAngle_ = 0.0f;
}

// 更新
void Box::Update() {
	worldTransform_.rotation_.x = IModel::LerpAnimation(EasingMode::kOutBack);
	IModel::Update();
}

// デバックテキスト
void Box::DebugText() { IModel::DebugText("box"); }

// 描画
void Box::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 舌
// 初期化
void Tongue::Initialize(Model* model, ViewProjection* viewProjection) { 
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, -0.6f, 1.0f};
	IModel::InitializeAnimation();
	startAngle_ = -110.0f;
	endAngle_ = 10.0f;
}

// 更新
void Tongue::Update() {
	worldTransform_.rotation_.x = IModel::LerpAnimation(EasingMode::kOutQuad);
	IModel::Update();
}

// デバックテキスト
void Tongue::DebugText() { IModel::DebugText("tongue"); }

// 描画
void Tongue::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 歯(上)
// 初期化
void ToothUp::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void ToothUp::Update() { IModel::Update(); }

// デバックテキスト
void ToothUp::DebugText() { IModel::DebugText("toothUp"); }

// 描画
void ToothUp::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 歯(下)
// 初期化
void ToothBottom::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void ToothBottom::Update() { IModel::Update(); }

// デバックテキスト
void ToothBottom::DebugText() { IModel::DebugText("toothBottom"); }

// 描画
void ToothBottom::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region ミミックのモデル

// デストラクタ
MimicModel::~MimicModel() {
	for (auto part : parts) {
		delete part;
	}
	parts.clear();
}

// 初期化
void MimicModel::Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection) {
	parts.resize((int)Parts::kPartsNum);
	parts[(int)Parts::kBox] = new Box();                 // 箱
	parts[(int)Parts::kLid] = new Lid();                 // 蓋
	parts[(int)Parts::kEye] = new Eye();                 // 目
	parts[(int)Parts::kToothUp] = new ToothUp();         // 上の歯
	parts[(int)Parts::kToothBottom] = new ToothBottom(); // 下の歯
	parts[(int)Parts::kTongue] = new Tongue();           // 舌
	// 初期化
	for (int i = 0; i < (int)Parts::kPartsNum; i++) {
		parts[i]->Initialize(models[i], viewProjection);
	}
}

// 更新
void MimicModel::Update() {
	for (auto part : parts) {
		part->Update();
#ifdef _DEBUG
		ImGui::Begin("mimic");
		part->DebugText();
		ImGui::End();
#endif // _DEBUG
	}
}

// 描画
void MimicModel::Draw() {
	for (auto part : parts) {
		part->Draw();
	}
}

// 親子付け
void MimicModel::SetParent(const WorldTransform* parent) {
	// 箱<-親
	parts[(int)Parts::kBox]->SetParent(parent);
	// 下の歯<-箱
	parts[(int)Parts::kToothBottom]->SetParent(&parts[(int)Parts::kBox]->GetWorldTransform());
	// 舌<-箱
	parts[(int)Parts::kTongue]->SetParent(&parts[(int)Parts::kBox]->GetWorldTransform());
	// 蓋<-親
	parts[(int)Parts::kLid]->SetParent(parent);
	// 目<-蓋
	parts[(int)Parts::kEye]->SetParent(&parts[(int)Parts::kLid]->GetWorldTransform());
	// 上の歯<-蓋
	parts[(int)Parts::kToothUp]->SetParent(&parts[(int)Parts::kLid]->GetWorldTransform());
}
#pragma endregion
