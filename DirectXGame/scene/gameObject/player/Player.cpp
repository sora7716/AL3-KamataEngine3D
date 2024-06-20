#define NOMINMAX
#include "Player.h"
#include "input/Input.h"
#include "gameObject/mapChipField/MapChipField.h"
#include <cassert>
#include <algorithm>
#include <numbers>
#include <array>
#define OneFrame 1.0f/60.0f
using namespace std;
//プレイヤーの初期化
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) { 

	assert(model);
	model_ = model;//モデル
	textureHandle_ = textureHandle;//テクスチャ
	worldTransform_.Initialize();//ワールド変換データの初期化
	worldTransform_.translation_ = position;//positionの上書き
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;//横向かせる
	viewProjection_ = viewProjection;//ビュープロジェクション

}

//プレイヤーの更新処理
void Player::Update() {
	//キー入力を受け取る箱
	bool leftPush  = Input::GetInstance()->PushKey(DIK_LEFT);
	bool rightPush = Input::GetInstance()->PushKey(DIK_RIGHT);
	bool upPush    = Input::GetInstance()->PushKey(DIK_UP);
	// 着地フラグ
	bool landing = false;
	// 地面との当たり判定
	// 降下中?
	if (velocity_.y < 0.0f) {
		// Y座標が地面いかになったら着地
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}
	// ジャンプ開始
	if (velocity_.y > 0.0f) {
		// 空中状態に移行
		onGround_ = false;
	} else {
		// 着地
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = kAcceleration / (kAcceleration / 2.0f);
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuation);
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}
	//速度の加算
	worldTransform_.translation_ += velocity_;
	if (onGround_) {
		// キー入力
		if (leftPush || rightPush) {
			Vector3 acceleration = {}; // 加速度
			if (rightPush) {
				acceleration.x += kAcceleration;
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				// プレイヤーの向いている向きを決定
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーの設定
					turnTimer_ = kTimeTurn;
				}
			} else if (leftPush) {
				acceleration.x -= kAcceleration;
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				// プレイヤーの向いている向きを決定
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーの設定
					turnTimer_ = kTimeTurn;
				}
			}
			// 加速/減速
			velocity_ += acceleration;

			// 最大速度制限
			velocity_.x = clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			//徐々に減速していって止まる
			velocity_.x *= (1.0f - kAttenuation);
		}
		if (upPush) {
			//ジャンプの初速
			Vector3 velocity = {0.0f, kJumpAcceleration, 0.0f};
			velocity_ += velocity;
		}

	}
	else {
		//落下速度
		velocity_ += Vector3(0.0f, -kGravityAcceleration, 0.0f);
		//落下速度制限
		velocity_.y = max(velocity_.y, -kLimitFallSpeed);
	}
	if (turnTimer_ > 0.0f) {
		//ワンフレームずつ加算
		turnTimer_ -= OneFrame;
		//時間を計測
		float timeRotation = 1.0f + turnTimer_ / kTimeTurn;
		//イージングする動きを計算
		float easing = 1.0f - powf(1.0f - timeRotation, 3.0f);
		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {
		    numbers::pi_v<float> / 2.0f,
		    numbers::pi_v<float> * 3.0f / 2.0f,
		};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		//現在の角度を求める
		float nowPosition = lerp(turnFirstRotationY_, destinationRotationY, easing);
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = nowPosition;
	}

	//衝突判定の初期化
	CollisionMapChipInfo collisionMapChipInfo;
	//移動量のコピー
	collisionMapChipInfo.velocity = velocity_;
	//マップ衝突チェック
	CollisionMapChip(collisionMapChipInfo);

	// アフィン変換
	worldTransform_.UpdateMatrix();
}

//プレイヤーの描画処理
void Player::Draw() { 

	model_->Draw(worldTransform_,*(viewProjection_),textureHandle_); 

}

//ワールドトランスフォームのゲッター
WorldTransform& Player::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

//ベロシティのゲッター
const Vector3 Player::GetVelocity() { 
	return velocity_; 
}

//どの向きを向いているのかのゲッター
const Player::LRDirection& Player::GetLRDirection() {
	// TODO: return ステートメントをここに挿入します
	return lrDirection_;
}

//マップチップのセッター
void Player::SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

#pragma warning(push)
#pragma warning(disable : 4100) // 一時的にエラーをなかったことにする(4100のエラーコード)
void Player::CollisionMapChip(CollisionMapChipInfo& info) { 
	MapChipTop(info); 
	MapChipBottom(info); 
	MapChipRight(info); 
	MapChipLeft(info); 

	IsCollision(info);

	CollisionMoveMent(info);
}

void Player::MapChipTop(CollisionMapChipInfo& info) { 
	array<Vector3, kNumCorner> positionNew; 
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_+info.velocity, static_cast<Corner>(i));
	}
	if (info.velocity.y <= 0.0f) {
		return;
	}
	MapChipType mapChipType;
	bool hit = false;
	MapChipField::IndexSet indexSet;
	indexSet    = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ - kHeight) + velocity_);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.velocity.y = max(0.0f, velocity_.y);
		info.celling = true;
	}
}

void Player::MapChipBottom(CollisionMapChipInfo& info) {
	array<Vector3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
	}
	if (info.velocity.y >= 0.0f) {
		return;
	}
	MapChipType mapChipType;
	bool hit = false;
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ + kHeight) + velocity_);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.velocity.y = min(0.0f, velocity_.y);
		info.landing = true;
	}
}

void Player::MapChipRight(CollisionMapChipInfo& info) {
	array<Vector3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
	}
	if (info.velocity.x >= 0.0f) {
		return;
	}
	MapChipType mapChipType;
	bool hit = false;
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ + kWidth) + velocity_);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.velocity.y = min(0.0f, velocity_.x);
		info.hitWall = true;
	}
}

void Player::MapChipLeft(CollisionMapChipInfo& info) {
	array<Vector3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
	}
	if (info.velocity.x <= 0.0f) {
		return;
	}
	MapChipType mapChipType;
	bool hit = false;
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ - kWidth) + velocity_);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.velocity.y = max(0.0f, velocity_.x);
		info.hitWall = true;
	}
}

void Player::CollisionMoveMent(CollisionMapChipInfo& info) {
	info.velocity = velocity_;
	worldTransform_.translation_ += info.velocity; 
}

void Player::IsCollision(const CollisionMapChipInfo& info) {
	if (info.celling) {
		velocity_.y = 0.0f;
	}
	if (info.landing) {
		velocity_.y = 0.0f;
		worldTransform_.translation_.y = kAcceleration / (kAcceleration / 2.0f);
	}
	if (info.hitWall) {
		velocity_.x *= (1.0f-kAttenuationWall);
	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) { 
	Vector3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0.0f}, //  kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f}, //  kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0.0f}, //  kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0.0f}, //  kLeftBottom
	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}
