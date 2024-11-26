#include "MimicModel.h"

#pragma region 蓋
// 初期化
void Rid::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void Rid::Update() { IModel::Update(); }

// デバックテキスト
void Rid::DebugText() { IModel::Draw(); }

// 描画
void Rid::Draw() {}
#pragma endregion

#pragma region 目
// 初期化
void Eye::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void Eye::Update() { IModel::Update(); }

// デバックテキスト
void Eye::DebugText() { IModel::Draw(); }

// 描画
void Eye::Draw() {}
#pragma endregion

#pragma region 箱
// 初期化
void Box::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void Box::Update() { IModel::Update(); }

// デバックテキスト
void Box::DebugText() { IModel::Draw(); }

// 描画
void Box::Draw() {}
#pragma endregion

#pragma region 舌
// 初期化
void Tongue::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void Tongue::Update() { IModel::Update(); }

// デバックテキスト
void Tongue::DebugText() { IModel::Draw(); }

// 描画
void Tongue::Draw() {}
#pragma endregion

#pragma region 歯(上)
// 初期化
void ToothUp::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void ToothUp::Update() { IModel::Update(); }

// デバックテキスト
void ToothUp::DebugText() { IModel::Draw(); }

// 描画
void ToothUp::Draw() {}
#pragma endregion

#pragma region 歯(下)
// 初期化
void ToothBottom::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void ToothBottom::Update() { IModel::Update(); }

// デバックテキスト
void ToothBottom::DebugText() { IModel::Draw(); }

// 描画
void ToothBottom::Draw() {}
#pragma endregion

#pragma region ミミックのモデル

// 初期化
void MimicModel::Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection) {
	parts.resize((int)Parts::kPartsNum);
	parts[(int)Parts::kBox] = new Box();                 // 箱
	parts[(int)Parts::kRid] = new Rid();                 // 蓋
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
		/*ImGui::Begin("mimic");
		part->DebugText();
		ImGui::End();*/
#endif // _DEBUG
	}
}

// 描画
void MimicModel::Draw() {
	for (auto part : parts) {
		part->Draw();
	}
}
#pragma endregion
