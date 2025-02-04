#include "PlayerParts.h"
#include "assets/gameManager/math/Math.h"
#pragma region 髪
// 初期化
void Hair::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void Hair::Update() { BaseModel::Update(); }

// 描画
void Hair::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 顔
// 初期化
void Face::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void Face::Update() { BaseModel::Update(); }

// 描画
void Face::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 眉毛
// 初期化
void EyeBrows::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void EyeBrows::Update() { BaseModel::Update(); }

// 描画
void EyeBrows::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 体
// 初期化
void Body::Initialize(ViewProjection* viewProjection, Model* model) { 
	BaseModel::Initialize(viewProjection, model); 
	worldTransform_.rotation_ = {0.0f, pi_f, 0.0f};
}

// 更新
void Body::Update() { BaseModel::Update(); }

// 描画
void Body::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 左もも
// 初期化
void LeftThigh::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void LeftThigh::Update() { BaseModel::Update(); }

// 描画
void LeftThigh::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 左足
// 初期化
void LeftLeg::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void LeftLeg::Update() { BaseModel::Update(); }

// 描画
void LeftLeg::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 右もも
// 初期化
void RightThigh::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void RightThigh::Update() { BaseModel::Update(); }

// 描画
void RightThigh::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 右足
// 初期化
void RightLeg::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void RightLeg::Update() { BaseModel::Update(); }

// 描画
void RightLeg::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 服(上)
// 初期化
void UpperCloth::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void UpperCloth::Update() { BaseModel::Update(); }

// 描画
void UpperCloth::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 服(下)
// 初期化
void LowerCloth::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void LowerCloth::Update() { BaseModel::Update(); }

// 描画
void LowerCloth::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 左腕
// 初期化
void LeftArm::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void LeftArm::Update() { BaseModel::Update(); }

// 描画
void LeftArm::Draw() { BaseModel::Draw(); }
#pragma endregion

#pragma region 右腕
// 初期化
void RightArm::Initialize(ViewProjection* viewProjection, Model* model) { BaseModel::Initialize(viewProjection, model); }

// 更新
void RightArm::Update() { BaseModel::Update(); }

// 描画
void RightArm::Draw() { BaseModel::Draw(); }
#pragma endregion
