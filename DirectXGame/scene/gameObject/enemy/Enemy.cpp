#define NOMINMAX
#include "Enemy.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>
#define pi_f          numbers::pi_v<float>
#define oneFream      1.0f / 60.0f
#define Radian(theta) theta * (1.0f / 180.0f) * pi_f
#include "gameObject/mapChipField/MapChipField.h"
#include "calculate/Aithmetic.h"
using namespace std;

// コンストラクタ
Enemy::Enemy() {
	model_ = nullptr;
	viewProjection_ = nullptr;
	textureHandle_ = 0u;
	velocity_ = {};
	mapChipField_ = nullptr;
	onGround_ = false;
	walkTimer_ = 0.0f;
}

// デストラクタ
Enemy::~Enemy() {}

// 初期化
void Enemy::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();              // ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;   // 最初のポジション
	worldTransform_.rotation_.y = pi_f / 2.0f; // 横向かせる
	velocity_ = {-kWalkSpeed, 0.0f, 0.0f};     // 歩行する速度
	onGround_ = true;                          // 地上にいるかどうかのフラグ
	walkTimer_ = 0.0f;                         // 経過時間
}

// 更新処理
void Enemy::Update() {
	// アニメーション
	walkTimer_ += oneFream;                                                            // 経過時間
	float param = sin(kWalkMotionAngleEnd * walkTimer_ / kWalkMotionTime);             // 角度を計算
	float theta = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f; // 線形補間
	worldTransform_.rotation_.x = Radian(theta);                                       // 弧度法に直す
	// 歩行
	worldTransform_.translation_ += velocity_;

	if (onGround_) {
		// 速度代入
		velocity_.x = -kWalkSpeed;
	} else {
		// 落下速度
		velocity_ += Vector3(0.0f, -kGravityAcceleration, 0.0f);
		// 落下速度制限
		velocity_.y = max(velocity_.y, -kLimitFallSpeed);
	}
	// 衝突判定の初期化
	CollisionMapChipInfo collisionMapChipInfo;
	// 移動量のコピー
	collisionMapChipInfo.velocity = velocity_;
	// マップ衝突チェック
	CollisionMapChip(collisionMapChipInfo);
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画処理
void Enemy::Draw() { model_->Draw(worldTransform_, *(viewProjection_), textureHandle_); }

void Enemy::SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

// #pragma warning(push)
// #pragma warning(disable : 4100) // 一時的にエラーをなかったことにする(4100のエラーコード)
void Enemy::CollisionMapChip(CollisionMapChipInfo& info) {
	// 上
	MapChipTop(info);
	// 下
	MapChipBottom(info);
	// 右
	MapChipRight(info);
	// 左
	MapChipLeft(info);

	// 上に当たった場合
	IsCollisionTop(info);
	// 壁に当たった場合
	IsHitWall(info);
	// 着地状態と空中状態の切り替え
	SwitchOnGround(info);
}

void Enemy::MapChipTop(CollisionMapChipInfo& info) {
	array<Vector3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
	}
	if (info.velocity.y <= 0.0f) {
		return;
	}
	MapChipType mapChipType;
	bool hit = false;
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ + (kHeight / 2.0f)) + velocity_);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.velocity.y = max(0.0f, (rect.bottom - worldTransform_.translation_.y) - ((kHeight / 2.0f) + Blanc));
		info.celling = true;
	}
}

void Enemy::MapChipBottom(CollisionMapChipInfo& info) {
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
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	if (!hit) {
		onGround_ = false;
	}
	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ - (kHeight / 2.0f)) + velocity_);
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		info.velocity.y = min(0.0f, (rect.top - worldTransform_.translation_.y) + ((kHeight / 2.0f) + Blanc));
		info.landing = true;
	}
}

void Enemy::MapChipRight(CollisionMapChipInfo& info) {
	// プレイヤーの最終的にいる場所
	array<Vector3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
	}
	// 右方向に行っていなかったら抜ける
	if (info.velocity.x <= 0.0f) {
		return;
	}
	// マップチップのタイプ
	MapChipType mapChipType;
	// 当たっているかどうか
	bool hit = false;
	// プレイヤーの最終的にいるマップ番号
	MapChipField::IndexSet indexSet;
	// 右上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右下の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 当たっていたら
	if (hit) {
		// プレイヤーの最終的にいるポジション
		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ + (kWidth / 2.0f)) + velocity_);
		// マップチップの角を検出
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		// ブロックに埋め込まないようなvelocityを記録
		info.velocity.x = max(0.0f, (rect.right - worldTransform_.translation_.x) - (velocity_.x + Blanc));
		// 壁に当たっているかのフラグ
		info.hitWallRight = true;
	}
}

void Enemy::MapChipLeft(CollisionMapChipInfo& info) {
	// プレイヤーが最終的にいるポジション
	array<Vector3, kNumCorner> positionNew;
	for (uint32_t i = 0; i < positionNew.size(); i++) {
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
	}
	// 右に移動していたら抜ける
	if (info.velocity.x >= 0.0f) {
		return;
	}
	// マップチップの種類
	MapChipType mapChipType;
	// 当たっているかどうか
	bool hit = false;
	// プレイヤーが最終的にいるマップ番号
	MapChipField::IndexSet indexSet;
	// 左下の場合
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 左上の場合
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 当たっていたら
	if (hit) {
		// プレイヤーの採取的にいるポジション
		indexSet = mapChipField_->GetMapChipIndexSetByPosition((worldTransform_.translation_ - (kWidth / 2.0f)) + velocity_);
		// プレイヤーの角
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		// めり込まないようなvelocityの記録
		info.velocity.x = min(0.0f, (rect.left - worldTransform_.translation_.x) + ((kWidth / 2.0f) + Blanc));
		// 壁に当たっているかのフラグ
		info.hitWallLeft = true;
	}
}

void Enemy::MoveMent(CollisionMapChipInfo& info) { worldTransform_.translation_ += info.velocity; }

void Enemy::IsCollisionTop(const CollisionMapChipInfo& info) {
	if (info.celling) {
		velocity_.y = 0.0f;
	}
}

Vector3 Enemy::CornerPosition(const Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0.0f}, //  kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f}, //  kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0.0f}, //  kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0.0f}, //  kLeftBottom
	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}

void Enemy::SwitchOnGround(CollisionMapChipInfo& info) {
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
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		} else {
			// プレイヤーのポジション
			array<Vector3, kNumCorner> positionNew;
			for (uint32_t i = 0; i < positionNew.size(); i++) {
				positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
			}

			// マップチップの種類
			MapChipType mapChipType;

			// 真下の当たり判定を行う
			bool hit = false;
			MapChipField::IndexSet indexSet; // ブロックがあるかどうか

			// leftBottomの場合
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kLeftBottom] + Vector3(0.0f, -kAttenuationLanding, 0.0f));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}
			// rightBottomの場合
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionNew[kRightBottom] + Vector3(0.0f, -kAttenuationLanding, 0.0f));
			mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
			if (mapChipType == MapChipType::kBlock) {
				hit = true;
			}
			// 真下に何もなかったら重力を付ける
			if (!hit) {
				onGround_ = false;
			}
			// 着地
			if (landing) {
				// めり込み排斥
				worldTransform_.translation_.y = 2.0f;
				// 摩擦で横方向速度が減衰する
				velocity_.x *= (1.0f - kAttenuation);
				// 下方向速度をリセット
				velocity_.y = 0.0f;
				// 接地状態に移行
				onGround_ = true;
			}
		}

	} else {
		if (info.landing) {
			onGround_ = true;
			// 着地時のX速度を減衰
			velocity_.x *= (1.0f - kAttenuationLanding);
			// Yの速度をゼロにする
			velocity_.y = 0.0f;
		}
	}
}

void Enemy::IsHitWall(const CollisionMapChipInfo& info) {
	// 壁接触による減速
	if (info.hitWallRight || info.hitWallLeft) {
		velocity_.x *= (1.0f - kAttenuationWall);
	}
}