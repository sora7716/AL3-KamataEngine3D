#include "Player.h"
#include "Model.h"
#include "asset/math/Aithmetic.h"
#include "input/Input.h"
#include <cassert>

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() {}

// 初期化
void Player::Initialize(Model* model, ViewProjection* viewProjection, uint32_t texture) {
	assert(model);
	model_ = model;                   // モデル
	viewProjection_ = viewProjection; // ビュープロジェクション
	texture_ = texture;               // テクスチャ
	worldTransform_.Initialize();     // ワールドトランスフォームの初期化
	input_ = Input::GetInstance();    // シングルインスタンス
}

// 更新
void Player::Update() {
	// デバックテキスト
	DebugText();

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += velocity_;

	// マトリックスの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, texture_); }

//速度
void Player::SetVelocity(Vector3 velocity) { velocity_ = velocity; }

#ifdef _DEBUG
#include "imgui.h"
void Player::DebugText() { 
	ImGui::Begin("Player"); 
	ImGui::DragFloat3("playerPosition", &worldTransform_.translation_.x);
	ImGui::End();
}
#endif // _DEBUG


//左へ移動
void Player::MoveLeft() { velocity_.x -= kCharacterSpeed; }

//右へ移動
void Player::MoveRight() { velocity_.x += kCharacterSpeed; }

//下へ移動
void Player::MoveDown() { velocity_.y -= kCharacterSpeed; }

//上へ移動
void Player::MoveUp() { velocity_.y += kCharacterSpeed; }

//右回り
void Player::RotateRight() { worldTransform_.rotation_.y -= kRotSpeed; }

//左回り
void Player::RotateLeft() { worldTransform_.rotation_.y += kRotSpeed; }
