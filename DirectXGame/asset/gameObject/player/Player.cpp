#define NOMINMAX
#include "Player.h"
#include "ViewProjection.h"
#include "asset/create/Create.h"
#include <cassert>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include <numbers>
#include <algorithm>
using namespace std;
using namespace std::numbers;

void Player::Initialize(Create* create, ViewProjection* viewProjection) {

	/// NULLポインタチェック
	assert(create);
	create_ = create;
	/// メンバ変数に引数のデータを記録する
	viewProjection_ = viewProjection;

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;//カメラからの距離
	worldTransform_.rotation_.y = pi_v<float> / 2.0f;//あとで変えるかも今のところ下を向く

	// 速度
	velocity_ = {kCharacterSpeed, kCharacterSpeed, kCharacterSpeed};

	
	//パーツの生成
	CreateParts();
}

// 更新
void Player::Update() {

	MoveLimit();

#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	for (auto& playerPart : parts_) {
		playerPart->Update();
	}
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {
	for (auto& playerPart : parts_) {

		playerPart->Draw();
	}
}

void Player::MoveRight() { worldTransform_.translation_.x += velocity_.x; }

void Player::MoveLeft() { worldTransform_.translation_.x -= velocity_.x; }

void Player::MoveUp() { worldTransform_.translation_.y += velocity_.y; }

void Player::MoveDown() { worldTransform_.translation_.y -= velocity_.y; }

void Player::MoveLimit() {

	const float kLimitMoveX = 32.6f;
	float kLimitmoveY[2];
	kLimitmoveY[0] = 18.4f ,kLimitmoveY[1] = 16.12f;
	
	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kLimitMoveX, kLimitMoveX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kLimitmoveY[0], kLimitmoveY[1]);
}

// 親子関係を作る
void Player::SetPearent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

//ワールド座標のゲッター
Vector3 Player::GetWorldPosition() { 
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

// AABBのゲッター
AABB Player::GetAABB() {
	Vector3 worldPosition = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPosition.x - kWidth / 2.0f, worldPosition.y - kHeight / 2.0f, worldPosition.z - kDepth / 2.0f};
	aabb.max = {worldPosition.x + kWidth / 2.0f, worldPosition.y + kHeight / 2.0f, worldPosition.z + kDepth / 2.0f};
	return aabb;
}

//ワールドトランスフォームのゲッター
WorldTransform& Player::GetWorldTransform(){
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// パーツを作る
void Player::CreateParts() {
	// プレイヤーパーツ(頭)
	parts_[static_cast<int>(IPlayerParts::head)] = make_unique<PlayerHead>();
	parts_[static_cast<int>(IPlayerParts::head)]->Initialize(create_->GetModel(create_->typePlayerHead), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::head)]->SetParent(&this->GetWorldTransform());

	// プレイヤーパーツ(体)
	parts_[static_cast<int>(IPlayerParts::body)] = make_unique<PlayerBody>();
	parts_[static_cast<int>(IPlayerParts::body)]->Initialize(create_->GetModel(create_->typePlayerBody), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::body)]->SetParent(&this->GetWorldTransform());

	// プレイヤーのパーツ(腕)
	parts_[static_cast<int>(IPlayerParts::arm)] = make_unique<PlayerArm>();
	parts_[static_cast<int>(IPlayerParts::arm)]->Initialize(create_->GetModel(create_->typePlayerLeft_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::arm)]->SetParent(&this->GetWorldTransform());
	// プレイヤーパーツ(左腕)
	parts_[static_cast<int>(IPlayerParts::left_Arm)] = make_unique<PlayerLeft_Arm>();
	parts_[static_cast<int>(IPlayerParts::left_Arm)]->Initialize(create_->GetModel(create_->typePlayerLeft_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::left_Arm)]->SetParent(&parts_[static_cast<int>(IPlayerParts::arm)]->GetWorldTransform());

	// プレイヤーパーツ(右腕)
	parts_[static_cast<int>(IPlayerParts::right_Arm)] = make_unique<PlayerRight_Arm>();
	parts_[static_cast<int>(IPlayerParts::right_Arm)]->Initialize(create_->GetModel(create_->typePlayerRight_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::right_Arm)]->SetParent(&parts_[static_cast<int>(IPlayerParts::arm)]->GetWorldTransform());
}