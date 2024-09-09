#define NOMINMAX
#include "Player.h"
#include "ViewProjection.h"
#include "asset/create/Create.h"
#include "asset/gameObject/hp/Hp.h"
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

	bulletModel_ = Model::Create();
	bulletWorldTransform_.Initialize();
	bulletWorldTransform_.translation_ = worldTransform_.translation_;
	bulletWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
}

// 更新
void Player::Update() {

	if (isDead_ ) {
		return;
	}

	MoveLimit();

	DrawDebugText();

	// パーツの更新
	for (auto& playerPart : parts_) {
		playerPart->Update();
	}

	static Vector3 begin = {};
	static Vector3 end = {};
	static float frame = 0;
	float endFrame = 60;
	static bool isReverse = false;
	bulletWorldTransform_.translation_ = worldTransform_.translation_;
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !isPressSpace_ && !isReverse) {
		begin = worldTransform_.translation_;
		end = Vector3(0.0f, 0.0f, 100.0f);
		isPressSpace_ = true;
		frame = 0.0f;
	}
	if (isPressSpace_) {
		if (frame++ > endFrame) {
			frame = endFrame;
			isReverse = true;
			isPressSpace_ = false;
			frame = 0.0f;
		}
		bulletWorldTransform_.translation_ = Math::Bezier(begin, begin + Vector3(20.0f, 0.0f, 30.0f), end, frame / endFrame);
	}
	if (isReverse) {
		if (frame++ > endFrame) {
			frame = endFrame;
			isReverse = false;
		}
		bulletWorldTransform_.translation_ = Math::Bezier(end, end + Vector3(20.0f, 0.0f, 30.0f), worldTransform_.translation_, Easing::InOut(frame / endFrame));
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
	bulletWorldTransform_.UpdateMatrix();
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

void Player::DrawDebugText() {

#ifdef _DEBUG

	ImGui::Begin("playerDebugWindow");
	if (ImGui::BeginChild("player")) {
		ImGui::Text("player");
		ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
		ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);

#pragma region 各パーツのデバッグテキストを呼び出す
	    parts_[static_cast<int>(IPlayerParts::head)]->DrawDebugText();      //頭
	    parts_[static_cast<int>(IPlayerParts::body)]->DrawDebugText();      //体
	    parts_[static_cast<int>(IPlayerParts::arm)]->DrawDebugText();       //両腕
	    parts_[static_cast<int>(IPlayerParts::left_Arm)]->DrawDebugText();  //左腕
	    parts_[static_cast<int>(IPlayerParts::right_Arm)]->DrawDebugText(); //右腕
	    parts_[static_cast<int>(IPlayerParts::ear)]->DrawDebugText();       //両耳
	    parts_[static_cast<int>(IPlayerParts::left_Ear)]->DrawDebugText();  //左耳
	    parts_[static_cast<int>(IPlayerParts::right_Ear)]->DrawDebugText(); //右耳
#pragma endregion

		ImGui::EndChild();
	}
	ImGui::End();
#endif // _DEBUG


}

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
void Player::SetPartsAngle(IPlayerParts::PartsName partsType, const Vector3& angle) {
	// 値をセット
	parts_[(int)partsType]->SetAngle(angle);
}

// パーツの位置のゲッター
Vector3 Player::GetPartsPosition(IPlayerParts::PartsName partsName) const { return parts_[(int)partsName]->GetPosition(); }

// パーツの角度のゲッター
Vector3 Player::GetPartsAngle(IPlayerParts::PartsName partsName) const { return parts_[(int)partsName]->GetAngle(); }

void Player::PlayerDead() { isDead_ = true; }

int Player::IsStartFrash() { return this->isFrashStart_; }

int Player::IsFrashing() { return this->isInvisible_; }

// パーツを作る
void Player::CreateParts() {
	// プレイヤーパーツ(頭)
	parts_[static_cast<int>(IPlayerParts::head)] = make_unique<PlayerHead>();
	// プレイヤーパーツ(体)
	parts_[static_cast<int>(IPlayerParts::body)] = make_unique<PlayerBody>();
	// プレイヤーのパーツ(腕)
	parts_[static_cast<int>(IPlayerParts::arm)] = make_unique<PlayerArm>();
	// プレイヤーパーツ(左腕)
	parts_[static_cast<int>(IPlayerParts::left_Arm)] = make_unique<PlayerLeft_Arm>();
	// プレイヤーパーツ(右腕)
	parts_[static_cast<int>(IPlayerParts::right_Arm)] = make_unique<PlayerRight_Arm>();
	// プレイヤーパーツ(耳)
	parts_[static_cast<int>(IPlayerParts::ear)] = make_unique<PlayerEar>();
	// プレイヤーパーツ(左耳)
	parts_[static_cast<int>(IPlayerParts::left_Ear)] = make_unique<PlayerLeft_Ear>();
	// プレイヤーパーツ(右耳)
	parts_[static_cast<int>(IPlayerParts::right_Ear)] = make_unique<PlayerRight_Ear>();
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
	parts_[static_cast<int>(IPlayerParts::left_Arm)]->Initialize(create_->GetModel(create_->typePlayerLeft_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::left_Arm)]->SetParent(&parts_[static_cast<int>(IPlayerParts::arm)]->GetWorldTransform());
	// プレイヤーパーツ(右腕)
	parts_[static_cast<int>(IPlayerParts::right_Arm)]->Initialize(create_->GetModel(create_->typePlayerRight_Arm), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::right_Arm)]->SetParent(&parts_[static_cast<int>(IPlayerParts::arm)]->GetWorldTransform());
	// プレイヤーパーツ(耳)
	parts_[static_cast<int>(IPlayerParts::ear)]->Initialize(create_->GetModel(create_->typePlayerLeft_Ear), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::ear)]->SetParent(&this->GetWorldTransform());
	// プレイヤーパーツ(左耳)
	parts_[static_cast<int>(IPlayerParts::left_Ear)]->Initialize(create_->GetModel(create_->typePlayerLeft_Ear), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::left_Ear)]->SetParent(&parts_[static_cast<int>(IPlayerParts::ear)]->GetWorldTransform());
	// プレイヤーパーツ(右耳)
	parts_[static_cast<int>(IPlayerParts::right_Ear)]->Initialize(create_->GetModel(create_->typePlayerRight_Ear), viewProjection_);
	parts_[static_cast<int>(IPlayerParts::right_Ear)]->SetParent(&parts_[static_cast<int>(IPlayerParts::ear)]->GetWorldTransform());
}

#pragma region プレイヤーの腕が吹っ飛ぶ処理

void Player::Right_Arm_MoveAngle() {

	static float right_ArmAngle = 1.0f;
	right_ArmAngle++;

	parts_[static_cast<int>(IPlayerParts::right_Arm)]->SetAngle({right_ArmAngle, right_ArmAngle, right_ArmAngle});
}

void Player::Right_Arm_MovePosition() {

	// 右腕の新しい位置を計算
	Vector3 right_ArmPos = {
	    parts_[static_cast<int>(IPlayerParts::right_Arm)]->GetPosition().x - 0.10f, parts_[static_cast<int>(IPlayerParts::right_Arm)]->GetPosition().y - 0.40f,
	    parts_[static_cast<int>(IPlayerParts::right_Arm)]->GetPosition().z - 0.75f};

	// 新しい位置を設定
	parts_[static_cast<int>(IPlayerParts::right_Arm)]->SetPosition(right_ArmPos);

	// 右腕の位置が一定の範囲内に入った場合、パーツを破壊済みに設定する
	if (right_ArmPos.x <= -10.f && right_ArmPos.y <= -40.f && right_ArmPos.z <= -90.f) {
		parts_[static_cast<int>(IPlayerParts::right_Arm)]->SetParts_IsDead(true);
	}
}

void Player::Right_Arm_Fly() {

	// 右腕のパーツが破壊されていないかまたは残機が1でないか確認する
	if (parts_[static_cast<int>(IPlayerParts::right_Arm)]->GetParts_IsDead() != false) {
		return;
	}

	// 右腕のパーツが飛んでいる状態に設定する
	parts_[static_cast<int>(IPlayerParts::right_Arm)]->SetParts_Fly(true);

	// パーツが飛んでいるかどうかを確認する
	if (parts_[static_cast<int>(IPlayerParts::right_Arm)]->GetParts_Fly()) {

		Right_Arm_MoveAngle();

		Right_Arm_MovePosition();
	}
}

void Player::Left_Arm_MoveAngle() {

	static float left_ArmAngle = 1.0f;
	left_ArmAngle++;

	parts_[static_cast<int>(IPlayerParts::left_Arm)]->SetAngle({left_ArmAngle, left_ArmAngle, left_ArmAngle});
}

void Player::Left_Arm_MovePosition() {

	// 左腕の新しい位置を計算
	Vector3 left_ArmPos = {
	    parts_[static_cast<int>(IPlayerParts::left_Arm)]->GetPosition().x - 0.10f, parts_[static_cast<int>(IPlayerParts::left_Arm)]->GetPosition().y - 0.40f,
	    parts_[static_cast<int>(IPlayerParts::left_Arm)]->GetPosition().z + 0.75f};

	// 新しい位置を設定
	parts_[static_cast<int>(IPlayerParts::left_Arm)]->SetPosition(left_ArmPos);

	// 左腕の位置が一定の範囲内に入った場合、パーツを破壊済みに設定する
	if (left_ArmPos.x <= -10.f && left_ArmPos.y <= -40.f && left_ArmPos.z >= 90.f) {
		parts_[static_cast<int>(IPlayerParts::left_Arm)]->SetParts_IsDead(true);
	}
}

void Player::Left_Arm_Fly() {

	// 左腕のパーツが破壊されていないか確認する
	if (parts_[static_cast<int>(IPlayerParts::left_Arm)]->GetParts_IsDead() != false) {
		return;
	}

	// 左腕のパーツが飛んでいる状態に設定する
	parts_[static_cast<int>(IPlayerParts::left_Arm)]->SetParts_Fly(true);

	// パーツが飛んでいるかどうかを確認する
	if (parts_[static_cast<int>(IPlayerParts::left_Arm)]->GetParts_Fly()) {

		Left_Arm_MoveAngle();

		Left_Arm_MovePosition();
	}
}

void (Player::*Player::parts_flyTable[])(){
	&Player::PlayerDead,
	&Player::Left_Arm_Fly, 
	&Player::Right_Arm_Fly
};

#pragma endregion

void Player::Unrivaled() {

	static int frashTimer = 0;
	const int kInterval = 15;

	if (isFrashStart_) {

		if (--frashTimer < 0 && isInvisible_ == false) {
			isInvisible_ = true;
			frashTimer = kInterval;
		} else if (--frashTimer < 0 && isInvisible_ == true) {
			isInvisible_ = false;
			frashTimer = kInterval;
		}
	}
}