#include "PlayerModel.h"

// 初期化
void PlayerModel::Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models) {
	parts[(int)Parts::kBody] = std::make_shared<Body>(); // 体
	parts[(int)Parts::kFace] = std::make_shared<Face>(); // 顔
	parts[(int)Parts::kEyeBrows] = std::make_shared<EyeBrows>(); // 眉毛
	parts[(int)Parts::kHair] = std::make_shared<Hair>(); // 髪
	parts[(int)Parts::kLeftArm] = std::make_shared<LeftArm>(); // 髪
	parts[(int)Parts::kRightArm] = std::make_shared<RightArm>(); // 髪
	parts[(int)Parts::kLeftThigh] = std::make_shared<LeftThigh>(); // 左もも
	parts[(int)Parts::kLeftLeg] = std::make_shared<LeftLeg>();     // 左足
	parts[(int)Parts::kRightThigh] = std::make_shared<RightThigh>(); // 右もも
	parts[(int)Parts::kRightLeg] = std::make_shared<RightLeg>();     // 右足
	parts[(int)Parts::kUpperCloth] = std::make_shared<UpperCloth>(); // 服(上)
	parts[(int)Parts::kLowerCloth] = std::make_shared<LowerCloth>(); // 服(下)
	for (int i = 0; i < parts.size(); i++) {
		parts[i]->Initialize(viewProjection, models[i].get());
	}
}

// 更新
void PlayerModel::Update() {
	for (auto part : parts) {
		part->Update();
	}
}

// 描画
void PlayerModel::Draw() {
	for (auto part : parts) {
		part->Draw();
	}
}

void PlayerModel::SetParent(const WorldTransform* parent) {
	// 親->体
	parts[(int)Parts::kBody]->SetParent(parent);
	// 体->顔
	parts[(int)Parts::kFace]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
	// 顔->髪
	parts[(int)Parts::kHair]->SetParent(parts[(int)Parts::kFace]->GetWorldTransform());
	// 顔->眉毛
	parts[(int)Parts::kEyeBrows]->SetParent(parts[(int)Parts::kFace]->GetWorldTransform());
	//体->左腕
	parts[(int)Parts::kLeftArm]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
	// 体->右腕
	parts[(int)Parts::kRightArm]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
	// 体->左もも
	parts[(int)Parts::kLeftThigh]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
	// 左もも->左足
	parts[(int)Parts::kLeftLeg]->SetParent(parts[(int)Parts::kLeftThigh]->GetWorldTransform());
	// 体->右もも
	parts[(int)Parts::kRightThigh]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
	// 右もも->右足
	parts[(int)Parts::kRightLeg]->SetParent(parts[(int)Parts::kRightThigh]->GetWorldTransform());
	// 体->服(上)
	parts[(int)Parts::kUpperCloth]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
	// 体->服(下)
	parts[(int)Parts::kLowerCloth]->SetParent(parts[(int)Parts::kBody]->GetWorldTransform());
}