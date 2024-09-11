#define NOMINMAX
#include "Player.h"
#include "ViewProjection.h"
#include "asset/create/Create.h"
#include "asset/gameObject/hp/Hp.h"
#include "asset/gameObject/skydome/SkyDome.h"
#include "asset/math/Math.h"
#include "input/Input.h"
#include <cassert>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include <algorithm>
#include <numbers>
using namespace std;
using namespace std::numbers;

// 初期化
void Player::Initialize(Create* create, ViewProjection* viewProjection) {

	/// NULLポインタチェック
	assert(create);
	create_ = create;
	/// メンバ変数に引数のデータを記録する
	viewProjection_ = viewProjection;

	/// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 50.0f;           // カメラからの距離
	worldTransform_.rotation_.y = pi_v<float> / 2.0f; // あとで変えるかも今のところ下を向く

	// 速度
	velocity_ = {kCharacterSpeed, kCharacterSpeed, kCharacterSpeed};

	// パーツの生成
	CreateParts();
	InitializeParts();
}

// 更新
void Player::Update(float firePos) {

	if (isDead_) {
		return;
	}

	MoveLimit();

#ifdef _DEBUG
	ImGui::Begin("player");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	// パーツの更新
	for (auto& playerPart : parts_) {
		playerPart->Update();
	}

	if (skyDome_) {
		// 耳を飛ばす
		EarShot(firePos);
	}

	if (hpCount_ < 3) {
		(this->*parts_flyTable[hpCount_])();
	}

	if (--coolTimer >= 0) {
		Unrivaled();
	} else {
		isFrashStart_ = false;
		isInvisible_ = false;
	}

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {

	if (isDead_ || isInvisible_) {
		return;
	}

	// パーツの描画
	for (auto& playerPart : parts_) {
		playerPart->Draw();
	}
}

// 衝突したとき
void Player::OnCollision(int hpCount) {

	hpCount_ = hpCount;

	isFrashStart_ = true;

	coolTimer = 60;
}

void Player::MoveRight() { worldTransform_.translation_.x += velocity_.x; }

void Player::MoveLeft() { worldTransform_.translation_.x -= velocity_.x; }

void Player::MoveUp() { worldTransform_.translation_.y += velocity_.y; }

void Player::MoveDown() { worldTransform_.translation_.y -= velocity_.y; }

void Player::MoveLimit() {

	const float kLimitMoveX = 32.6f;
	float kLimitmoveY[2];
	kLimitmoveY[0] = 17.2f, kLimitmoveY[1] = 19.6f;

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kLimitMoveX, kLimitMoveX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kLimitmoveY[0], kLimitmoveY[1]);
}

// 親子関係を作る
void Player::SetPearent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

// 位置のセッター
void Player::SetPosition(const Vector3& position) { worldTransform_.translation_ = position; }

// 角度のセッター
void Player::SetRotation(const Vector3& rotation) { worldTransform_.rotation_ = rotation; }

// ワールド座標のゲッター
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

// ワールドトランスフォームのゲッター
WorldTransform& Player::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// パーツの位置のセッター
void Player::SetPartsPosition(IPlayerParts::PartsName partsName, const Vector3& position) {
	// 値をセット
	parts_[(int)partsName]->SetPosition(position);
}

// パーツの角度
void Player::SetPartsAngle(IPlayerParts::PartsName partsName, const Vector3& angle) {
	// 値をセット
	parts_[(int)partsName]->SetAngle(angle);
}

// アニメーションを行うかどうかのフラグのセッター
void Player::SetPartsIsAnimation(IPlayerParts::PartsName partsName, bool isAnimation) {
	// 値をセット
	parts_[(int)partsName]->SetIsAnimation(isAnimation);
}

// パーツの位置のゲッター
Vector3 Player::GetPartsPosition(IPlayerParts::PartsName partsName) const { return parts_[(int)partsName]->GetPosition(); }

// パーツの角度のゲッター
Vector3 Player::GetPartsAngle(IPlayerParts::PartsName partsName) const { return parts_[(int)partsName]->GetAngle(); }

// プレイヤーの消滅
void Player::PlayerDead() { isDead_ = true; }

// 無敵時間がスタートするかどうかのフラグ
bool Player::IsStartFrash() { return this->isFrashStart_; }

// 透明なのかのフラグ
bool Player::IsInvisible_() { return this->isInvisible_; }

// 耳飛ばしたのが1回目かどうかのフラグ
void Player::SetIsShotFirstTime(bool isShotFirstTime) { isShotFirstTime_ = isShotFirstTime; }

// ワープポイントがスポーンしているかどうかのフラグ
bool Player::IsWarpSpawn() { return isWarpSpawn_; }

// セッタースカイドーム
void Player::SetSkyDome(SkyDome* skyDome) { skyDome_ = skyDome; }

// プレイヤーのスケール
void Player::SetScale(const Vector3& scale) { worldTransform_.scale_ = scale; }

// パーツを作る
void Player::CreateParts() {
	// プレイヤーパーツ(頭)
	parts_[static_cast<int>(IPlayerParts::head)] = make_unique<PlayerHead>();
	// プレイヤーパーツ(体)
	parts_[static_cast<int>(IPlayerParts::body)] = make_unique<PlayerBody>();
	// プレイヤーのパーツ(腕)
	parts_[static_cast<int>(IPlayerParts::arm)] = make_unique<PlayerArm>();
	// プレイヤーパーツ(左腕)
	parts_[static_cast<int>(IPlayerParts::left_arm)] = make_unique<PlayerLeft_Arm>();
	// プレイヤーパーツ(右腕)
	parts_[static_cast<int>(IPlayerParts::right_arm)] = make_unique<PlayerRight_Arm>();
	// プレイヤーパーツ(耳)
	parts_[static_cast<int>(IPlayerParts::ear)] = make_unique<PlayerEar>();
	// プレイヤーパーツ(左耳)
	parts_[static_cast<int>(IPlayerParts::left_ear)] = make_unique<PlayerLeft_Ear>();
	// プレイヤーパーツ(右耳)
	parts_[static_cast<int>(IPlayerParts::right_ear)] = make_unique<PlayerRight_Ear>();
}

// パーツの初期化
void Player::InitializeParts() {
	// プレイヤーパーツ(頭)
	parts_[static_cast<int>(IPlayerParts::head)]->Initialize(create_->GetModel(create_->typePlayerHead), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::head)]->SetParent(&this->GetWorldTransform());
	// プレイヤーパーツ(体)
	parts_[static_cast<int>(IPlayerParts::body)]->Initialize(create_->GetModel(create_->typePlayerBody), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::body)]->SetParent(&this->GetWorldTransform());
	// プレイヤーのパーツ(腕)
	parts_[static_cast<int>(IPlayerParts::arm)]->Initialize(create_->GetModel(create_->typePlayerLeft_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::arm)]->SetParent(&this->GetWorldTransform());
	// プレイヤーパーツ(左腕)
	parts_[static_cast<int>(IPlayerParts::left_arm)]->Initialize(create_->GetModel(create_->typePlayerLeft_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::left_arm)]->SetParent(&parts_[static_cast<int>(IPlayerParts::arm)]->GetWorldTransform());
	// プレイヤーパーツ(右腕)
	parts_[static_cast<int>(IPlayerParts::right_arm)]->Initialize(create_->GetModel(create_->typePlayerRight_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::right_arm)]->SetParent(&parts_[static_cast<int>(IPlayerParts::arm)]->GetWorldTransform());
	// プレイヤーパーツ(耳)
	parts_[static_cast<int>(IPlayerParts::ear)]->Initialize(create_->GetModel(create_->typePlayerLeft_Ear), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::ear)]->SetParent(&this->GetWorldTransform());
	// プレイヤーパーツ(左耳)
	parts_[static_cast<int>(IPlayerParts::left_ear)]->Initialize(create_->GetModel(create_->typePlayerLeft_Ear), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::left_ear)]->SetParent(&parts_[static_cast<int>(IPlayerParts::ear)]->GetWorldTransform());
	// プレイヤーパーツ(右耳)
	parts_[static_cast<int>(IPlayerParts::right_ear)]->Initialize(create_->GetModel(create_->typePlayerRight_Ear), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::right_ear)]->SetParent(&parts_[static_cast<int>(IPlayerParts::ear)]->GetWorldTransform());
}

// 耳を飛ばす
void Player::EarShot(float firePos) {
	static Vector3 beginPos = {};                   // 初めの位置
	static Vector3 endPos = {};                     // 終わりの位置
	static float beginSize = 1.0f;                  // 初めの大きさ
	static float endSize = 0.2f;                    // 終わりの大きさ
	static float frame = 0;                         // 現在のフレーム数
	float endFrame = 60.0f / (skyDome_->GetVelocityZ()*0.2f); // 最終的になってほしいフレーム数
	static bool isReverse = false;                  // 戻ってくる用のフラグ
	leftEarPosition_ = {};                          // 最初のポジション
	isWarpSpawn_ = isReverse;                       // 戻ってくるフラグの代入
	if (firePos < -800 && !isShotFirstTime_) {
		beginPos = leftEarPosition_;           // 初めの位置を設定
		endPos = Vector3(0.0f, 0.0f, -100.0f); // 終わりの位置の設定
		isEarShot_ = true;                     // 耳を飛ばすフラグをtrue
		isShotFirstTime_ = true;               // 1回目かどうかのフラグをtrue
		frame = 0.0f;                          // フレームを0に設定
	}
	if (isEarShot_) {
		if (frame++ > endFrame) {
			frame = endFrame;   // 現在のフレームを最終的になってほしいフレームで固定
			isReverse = true;   // 戻ってくるフラグをtrue
			isEarShot_ = false; // 耳を飛ばすフラグをfalse
			frame = 0.0f;
		}
		leftEarPosition_ = Math::Bezier(beginPos, beginPos + Vector3(-50.0f, 0.0f, -30.0f), endPos, frame / endFrame); // ベジエ曲線で動きをつけている
		leftEarSize_ = Math::Lerp(beginSize, endSize, Easing::OutSine(frame / endFrame));                                  // 大きさを変える
	}
	if (isReverse) {
		if (frame++ > endFrame) {
			frame = endFrame;
			isReverse = false;
		}
		leftEarPosition_ = Math::Bezier(endPos, endPos + Vector3(-50.0f, 0.0f, 30.0f), {-1.55f, 0.0f, 0.0f}, Easing::InOutSine(frame / endFrame));
		leftEarSize_ = Math::Lerp(endSize, beginSize, Easing::InSine(frame / endFrame)); // 大きさを変える
		if (leftEarSize_ < beginSize) {
			leftEarSize_ = beginSize; // サイズをbeginSizeより下に行かないようにする
		}
	}
	if (isReverse || isEarShot_) {
		// 位置を設定
		parts_[static_cast<int>(IPlayerParts::left_ear)]->SetPosition(leftEarPosition_);
		parts_[static_cast<int>(IPlayerParts::left_ear)]->SetSize({leftEarSize_, leftEarSize_, leftEarSize_});
	}
}

#pragma region プレイヤーの腕が吹っ飛ぶ処理

void Player::Right_Arm_MoveAngle() {

	static float right_ArmAngle = 1.0f;
	right_ArmAngle++;

	parts_[static_cast<int>(IPlayerParts::right_arm)]->SetAngle({right_ArmAngle, right_ArmAngle, right_ArmAngle});
}

void Player::Right_Arm_MovePosition() {

	// 右腕の新しい位置を計算
	Vector3 right_ArmPos = {
	    parts_[static_cast<int>(IPlayerParts::right_arm)]->GetPosition().x - 0.10f, parts_[static_cast<int>(IPlayerParts::right_arm)]->GetPosition().y - 0.40f,
	    parts_[static_cast<int>(IPlayerParts::right_arm)]->GetPosition().z - 0.75f};

	// 新しい位置を設定
	parts_[static_cast<int>(IPlayerParts::right_arm)]->SetPosition(right_ArmPos);

	// 右腕の位置が一定の範囲内に入った場合、パーツを破壊済みに設定する
	if (right_ArmPos.x <= -10.f && right_ArmPos.y <= -40.f && right_ArmPos.z <= -90.f) {
		parts_[static_cast<int>(IPlayerParts::right_arm)]->SetParts_IsDead(true);
	}
}

void Player::Right_Arm_Fly() {

	// 右腕のパーツが破壊されていないかまたは残機が1でないか確認する
	if (parts_[static_cast<int>(IPlayerParts::right_arm)]->GetParts_IsDead() != false) {
		return;
	}

	// 右腕のパーツが飛んでいる状態に設定する
	parts_[static_cast<int>(IPlayerParts::right_arm)]->SetParts_Fly(true);

	// パーツが飛んでいるかどうかを確認する
	if (parts_[static_cast<int>(IPlayerParts::right_arm)]->GetParts_Fly()) {

		Right_Arm_MoveAngle();

		Right_Arm_MovePosition();
	}
}

void Player::Left_Arm_MoveAngle() {

	static float left_ArmAngle = 1.0f;
	left_ArmAngle++;

	parts_[static_cast<int>(IPlayerParts::left_arm)]->SetAngle({left_ArmAngle, left_ArmAngle, left_ArmAngle});
}

void Player::Left_Arm_MovePosition() {

	// 左腕の新しい位置を計算
	Vector3 left_ArmPos = {
	    parts_[static_cast<int>(IPlayerParts::left_arm)]->GetPosition().x - 0.10f, parts_[static_cast<int>(IPlayerParts::left_arm)]->GetPosition().y - 0.40f,
	    parts_[static_cast<int>(IPlayerParts::left_arm)]->GetPosition().z + 0.75f};

	// 新しい位置を設定
	parts_[static_cast<int>(IPlayerParts::left_arm)]->SetPosition(left_ArmPos);

	// 左腕の位置が一定の範囲内に入った場合、パーツを破壊済みに設定する
	if (left_ArmPos.x <= -10.f && left_ArmPos.y <= -40.f && left_ArmPos.z >= 90.f) {
		parts_[static_cast<int>(IPlayerParts::left_arm)]->SetParts_IsDead(true);
	}
}

void Player::Left_Arm_Fly() {

	// 左腕のパーツが破壊されていないか確認する
	if (parts_[static_cast<int>(IPlayerParts::left_arm)]->GetParts_IsDead() != false) {
		return;
	}

	// 左腕のパーツが飛んでいる状態に設定する
	parts_[static_cast<int>(IPlayerParts::left_arm)]->SetParts_Fly(true);

	// パーツが飛んでいるかどうかを確認する
	if (parts_[static_cast<int>(IPlayerParts::left_arm)]->GetParts_Fly()) {

		Left_Arm_MoveAngle();

		Left_Arm_MovePosition();
	}
}

void (Player::*Player::parts_flyTable[])(){&Player::PlayerDead, &Player::Left_Arm_Fly, &Player::Right_Arm_Fly};

#pragma endregion

void Player::Unrivaled() {

	static int frashTimer = 0; // 点滅させる時間
	const int kInterval = 15;  // どれくらいのスパンで点滅させるか
	// 無敵時間の時に処理する
	if (isFrashStart_) {
		if (--frashTimer < 0 && isInvisible_ == false) {
			isInvisible_ = true;    // 透明化
			frashTimer = kInterval; // 時間を設定
		} else if (--frashTimer < 0 && isInvisible_ == true) {
			isInvisible_ = false;   // 非透明化
			frashTimer = kInterval; // 時間を設定
		}
	}
}