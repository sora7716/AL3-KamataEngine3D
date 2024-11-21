#include "Player.h"
#include "ViewProjection.h"
#include "Model.h"
#include "input/Input.h"
#include "assets/math/Math.h"
#include <cassert>
    //初期化
void Player::Initialize(ViewProjection* viewProjection, Model* model) { 
    assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

//更新
void Player::Update() { 
	
	//ゲームパッドの操作
	GamePadControl();
	
	//キーボードの操作
	KeyBoaeredControl();

	worldTransform_.UpdateMatrix();
}

//描画
void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

//ワールドトランスフォームのゲッター
WorldTransform& Player::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

//ゲームパッドの操作
void Player::GamePadControl() {
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;
		// 移動量
		Vector3 move = {(float)joyState.Gamepad.sThumbLX, 0.0f, (float)joyState.Gamepad.sThumbLY};
		// 移動量に速さを反映
		move = Math::Normalize(move) * speed;
		// 移動
		worldTransform_.translation_ += move;
	}
}

//キーボードの操作
void Player::KeyBoaeredControl() {
	Vector3 move{};
	const float speed = 0.3f;
	if (Input::GetInstance()->PushKey(DIK_D)) {
		move.x = 1.0f;
	} else if (Input::GetInstance()->PushKey(DIK_A)) {
		move.x = -1.0f;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		move.z = 1.0f;
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		move.z = -1.0f;
	}
	move = Math::Normalize(move) * speed;
	worldTransform_.translation_ += move;
}
