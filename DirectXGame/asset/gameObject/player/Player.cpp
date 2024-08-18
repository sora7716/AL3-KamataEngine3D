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
	DebugText();
	// キャラクターの移動ベクトル
	Vector3 move = {};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	// 押した方向でベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向でベクトルを変更(上下)
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	// マトリックスの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, texture_); }

#ifdef _DEBUG
#include "imgui.h"
void Player::DebugText() { 
	ImGui::Begin("Player"); 
	ImGui::DragFloat3("playerPosition", &worldTransform_.translation_.x);
	ImGui::End();
}
#endif // _DEBUG
