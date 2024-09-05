#include "Player.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include <numbers>
using namespace std;
using namespace std::numbers;

void Player::Initialize(Model* model, ViewProjection* viewProjection) {

	/// NULLポインタチェック
	assert(model);

	/// メンバ変数に引数のデータを記録する
	model_ = model;
	viewProjection_ = viewProjection;

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;//カメラからの距離
	worldTransform_.rotation_.y = pi_v<float> / 2.0f;//あとで変えるかも今のところ下を向く

	// 速度
	velocity_ = {kCharacterSpeed, kCharacterSpeed, kCharacterSpeed};
}

// 更新
void Player::Update() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_); // プレイヤー
}

void Player::MoveRight() { worldTransform_.translation_.x += velocity_.x; }

void Player::MoveLeft() { worldTransform_.translation_.x -= velocity_.x; }

void Player::MoveUp() { worldTransform_.translation_.y += velocity_.y; }

void Player::MoveDown() { worldTransform_.translation_.y -= velocity_.y; }

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

WorldTransform& Player::GetWorldTransform(){
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}
