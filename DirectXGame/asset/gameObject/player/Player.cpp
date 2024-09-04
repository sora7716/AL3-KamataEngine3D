#include "Player.h"
#include <cassert>
#include "Model.h"
#include "ViewProjection.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include <numbers>
using namespace std;
using namespace std::numbers;

void Player::Initialize(Model* model, ViewProjection* viewProjection) {

	///NULLポインタチェック
	assert(model);

	///メンバ変数に引数のデータを記録する
	model_ = model;
	viewProjection_ = viewProjection;

	///ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;//カメラからの距離
	worldTransform_.rotation_.y = pi_v<float>;//あとで変えるかも今のところ下を向く

	//速度
	velocity_ = {kCharacterSpeed, kCharacterSpeed, kCharacterSpeed};
}

//更新
void Player::Update() {
#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
	
	//行列の更新
	worldTransform_.UpdateMatrix();
}

//描画
void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_); // プレイヤー
}

void Player::MoveRight() {
	worldTransform_.translation_.x += velocity_.x;
}

void Player::MoveLeft() {
	worldTransform_.translation_.x -= velocity_.x;
}

void Player::MoveUp() { 
	worldTransform_.translation_.y += velocity_.y; 
}

void Player::MoveDown() { 
	worldTransform_.translation_.y -= velocity_.y; 
}

//親子関係を作る
void Player::SetPearent(const WorldTransform* parent) { 
	worldTransform_.parent_ = parent; 
}
