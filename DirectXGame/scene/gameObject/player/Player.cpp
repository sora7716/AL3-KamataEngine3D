#define NOMINMAX
#include "Player.h"
#include <cassert>
#include <numbers>
#include <algorithm>
#define oneFrame 1.0f / 60.0f
using namespace std;
//プレイヤーの初期化
void Player::Initialize(Model* model, const uint32_t &textureHandle, ViewProjection* viewProjection, const Vector3& position) { 

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 5.0f / 2.0f;
	viewProjection_ = viewProjection;

}

//プレイヤーの更新処理
void Player::Update() { Action(); /*プレイヤーのキー入力しているときとしていないときの動き*/ } 

//プレイヤーの急ブレーキ
void Player::Brake(bool isBrake) { 
	if (isBrake) {
		velocity_.SetVector({velocity_.GetVector().x * (1.0f - kAttenuation), velocity_.GetVector().y, velocity_.GetVector().z});//x座標に急ブレーキ
	}
}

//プレイヤーの速度
void Player::Velocity(Vector3 acceleration) {
	velocity_ += acceleration;// 速度に加速度を加算
	velocity_.SetVector({clamp(velocity_.GetVector().x, -kLimitRunSpeed, kLimitRunSpeed), velocity_.GetVector().y, velocity_.GetVector().z}); // 最大速度制限
}

//キー入力していないとの減速
float Player::Deceleration() {
	float attenuation = velocity_.GetVector().x;
	attenuation *= (1 - kAttenuation);//減速
	if (velocity_.GetVector().x * velocity_.GetVector().x < 0.001f) {
		return  0.0f;//動いているかわからないぐらいの速度になったら完全に止める
	}

	return attenuation;//減速している値を返す
}

//プレイヤーの行動
void Player::Action() {
	
	Place();//プレイヤーのいる場所

	Brake(isBrake_); // プレイヤーが振り向くときの急ブレーキ

	Angle(); // プレイヤーの向き

    worldTransform_.UpdateMatrix(); // 行列の更新
}

//プレイヤーの向き
void Player::Direction(LRDirection direction) {
	if (lrDirection_ != direction) {
		RecordAngleAndTime();//アングルとタイマーの記録
		lrDirection_ = direction;//向き
	}
}

//アングルとタイマーの記録
void Player::RecordAngleAndTime() {
	turnFirstRotationY_ = worldTransform_.rotation_.y;//現在の角度を格納
	turnTimer_ = kTimeTurn;//タイマーのセット
}

//振り向きアニメーション
float Player::TurnAround(float *destinationRotationYTable) {
	float timeRation = 1 - turnTimer_ / kTimeTurn; // 0から1に下がっている値を1から0に上がっていくようにするために「1-」している
	float easing = 1.0f - powf(1.0f - timeRation, 3.0f);//イージングする計算

	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];//どの角度化の選択
	float nowRotation = lerp(turnFirstRotationY_, destinationRotationY, easing);//今の角度を計算

	return nowRotation;
}

//プレイヤーの向き
void Player::Angle() {
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= oneFrame;//1フレームを加算
		float destinationRotationYTable[] = {std::numbers::pi_v<float> * 5.0f / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};//向いてほしい角度の代入
		worldTransform_.rotation_.y = TurnAround(destinationRotationYTable);//最終的な向いている角度を代入
	}
}

 // プレイヤーのブレーキと向く方向
void Player::Movement(LRDirection direction) {

	// 左移動中の右入力
	if (velocity_.GetVector().x < 0.0f) {

		isBrake_ = true; // 速度と逆方向に入力中は急ブレーキ
	}

	Direction(direction); // 向きたい方向
}

//プレイヤーが地上にいるときの行動
void Player::OnGround() {
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		Vector3 acceleration = {}; // プレイヤーの加速度を作成
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAcceleration; // 加速度の加算
			Movement(LRDirection::kRight);   // プレイヤーにしてほしい動き

		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.x -= kAcceleration; // 加速度を減算
			Movement(LRDirection::kLeft);    // プレイヤーにしてほしい動き
		}
		Velocity(acceleration); // 移動
	} else {
		isBrake_ = false;                                                                        // ブレーキのフラグをリセット
		velocity_.SetVector({Deceleration(), velocity_.GetVector().y, velocity_.GetVector().z}); // 減速した値を代入
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		velocity_ += Vector3(velocity_.GetVector().x, kJumpAcceleration, velocity_.GetVector().z);
	}
}

//プレイヤーのいる位置
void Player::Place() {
	worldTransform_.translation_ += velocity_; // translate_にvelocity_を加算
	// プレイヤーが地上にいるとき
	if (onGround_) {
		OnGround();
		if (velocity_.GetVector().y > 0.0f) {
			onGround_ = false;
		}
	} else {                                                                                                                     // プレイヤーが地上にいないとき
		velocity_ += Vector3(0.0f, -kGravityAcceleration, 0.0f);                                                                 // 落下速度
		velocity_.SetVector({velocity_.GetVector().x, max(velocity_.GetVector().y, -kLimitFallSpeed), velocity_.GetVector().z}); // 落下速度制限
		bool landing = false;                                                                                                    // 着陸したかどうか
		if (velocity_.GetVector().y < 0.0f) {
			if (worldTransform_.translation_.GetVector().y <= 1.0f) {
				landing = true;
			}
		}
		if (landing) {
			worldTransform_.translation_.SetVector({worldTransform_.translation_.GetVector().x, 2.0f, worldTransform_.translation_.GetVector().z});

			velocity_.SetVector({velocity_.GetVector().x * (1.0f - kAttenuationLading), 0.0f, velocity_.GetVector().z});
			onGround_ = true;
		}
	}
}


//プレイヤーの描画処理
void Player::Draw() { model_->Draw(worldTransform_,*(viewProjection_),textureHandle_); }