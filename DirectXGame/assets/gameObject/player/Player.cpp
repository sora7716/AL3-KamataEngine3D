#include "Player.h"

void Player::Initialize(Create* create, ViewProjection* viewProjection) {

	assert(create);

	create_ = create;

	worldTransform_.Initialize();

	viewProjection_ = viewProjection;

	
	InitializeParts();

}

void Player::Update() {

	for (auto& playerParts : parts) {
		playerParts->Update();
	}

	worldTransform_.UpdateMatrix();

}

void Player::Draw() {

	for (auto& playerParts : parts) {
		playerParts->Draw();
	}
}

///パーツ制作
void Player::CreateParts() {

	// 体
	parts[(int)IPlayerParts::body] = make_unique<PlayerBody>();

	// 頭
	parts[(int)IPlayerParts::head] = make_unique<PlayerHead>();

#pragma region 右側

	// 右上腕
	parts[(int)IPlayerParts::right_UpperArm] = make_unique<PlayerRight_UpperArm>();

	// 右腕
	parts[(int)IPlayerParts::right_LowerArm] = make_unique<PlayerRight_LowerArm>();
	
	// 右もも
	parts[(int)IPlayerParts::right_Thigh] = make_unique<PlayerRight_Thigh>();

	// 右足
	parts[(int)IPlayerParts::right_Leg] = make_unique<PlayerRight_Leg>();

#pragma endregion

#pragma region 左側

	// 左上腕
	parts[(int)IPlayerParts::left_UpperArm] = make_unique<PlayerLeft_UpperArm>();

	// 左腕
	parts[(int)IPlayerParts::left_LowerArm] = make_unique<PlayerLeft_LowerArm>();

	// 左もも
	parts[(int)IPlayerParts::left_Thigh] = make_unique<PlayerLeft_Thigh>();

	// 左足
	parts[(int)IPlayerParts::left_Leg] = make_unique<PlayerLeft_Leg>();

#pragma endregion

}

///パーツ初期化
void Player::InitializeParts() {

	/// パーツ制作
	CreateParts();

	/// 体
	parts[(int)IPlayerParts::body]->Initialize(create_->GetModel(create_->typeBody), viewProjection_);
	parts[(int)IPlayerParts::body]->SetParent(&this->GetWorldPosition());

	/// 頭
	parts[(int)IPlayerParts::head]->Initialize(create_->GetModel(create_->typeHead), viewProjection_);
	parts[(int)IPlayerParts::head]->SetParent(&parts[(int)IPlayerParts::body]->GetWorldTransform());

#pragma region 右側のパーツ

	// 右上腕
	parts[(int)IPlayerParts::right_UpperArm]->Initialize(create_->GetModel(create_->typeRight_UpperArm), viewProjection_);
	parts[(int)IPlayerParts::right_UpperArm]->SetParent(&parts[(int)IPlayerParts::body]->GetWorldTransform());

	// 右腕
	parts[(int)IPlayerParts::right_LowerArm]->Initialize(create_->GetModel(create_->typeRight_LowerArm), viewProjection_);
	parts[(int)IPlayerParts::right_LowerArm]->SetParent(&parts[(int)IPlayerParts::right_UpperArm]->GetWorldTransform());

	// 右もも
	parts[(int)IPlayerParts::right_Thigh]->Initialize(create_->GetModel(create_->typeRight_Thigh), viewProjection_);
	parts[(int)IPlayerParts::right_Thigh]->SetParent(&parts[(int)IPlayerParts::body]->GetWorldTransform());

	// 右足
	parts[(int)IPlayerParts::right_Leg]->Initialize(create_->GetModel(create_->typeLeft_Leg), viewProjection_);
	parts[(int)IPlayerParts::right_Leg]->SetParent(&parts[(int)IPlayerParts::right_Thigh]->GetWorldTransform());

#pragma endregion

#pragma region 左側のパーツ

	// 左上腕
	parts[(int)IPlayerParts::left_UpperArm]->Initialize(create_->GetModel(create_->typeLeft_UpperArm), viewProjection_);
	parts[(int)IPlayerParts::left_UpperArm]->SetParent(&parts[(int)IPlayerParts::body]->GetWorldTransform());

	// 左腕
	parts[(int)IPlayerParts::left_LowerArm]->Initialize(create_->GetModel(create_->typeLeft_LowerArm), viewProjection_);
	parts[(int)IPlayerParts::left_LowerArm]->SetParent(&parts[(int)IPlayerParts::left_UpperArm]->GetWorldTransform());

	// 左もも
	parts[(int)IPlayerParts::left_Thigh]->Initialize(create_->GetModel(create_->typeLeft_Thigh), viewProjection_);
	parts[(int)IPlayerParts::left_Thigh]->SetParent(&parts[(int)IPlayerParts::body]->GetWorldTransform());

	// 左足
	parts[(int)IPlayerParts::left_Leg]->Initialize(create_->GetModel(create_->typeLeft_Leg), viewProjection_);
	parts[(int)IPlayerParts::left_Leg]->SetParent(&parts[(int)IPlayerParts::left_Thigh]->GetWorldTransform());

#pragma endregion
};