#define NOMINMAX
#include "Player.h"
#include "ViewProjection.h"
#include "asset/create/Create.h"
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

	// プレイヤーの動ける位置の制限
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

	// 耳を飛ばす
	EarShot(firePos);

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {

	// パーツの描画
	for (auto& playerPart : parts_) {
		playerPart->Draw();
	}
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

// 耳飛ばしたのが1回目かどうかのフラグ
void Player::SetIsShotFirstTime(bool isShotFirstTime) { isShotFirstTime_ = isShotFirstTime; }

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
	static Vector3 beginPos = {};  // 初めの位置
	static Vector3 endPos = {};    // 終わりの位置
	static float beginSize = 1.0f; // 初めの大きさ
	static float endSize = 0.8f;   // 終わりの大きさ
	static float frame = 0;        // 現在のフレーム数
	float endFrame = 60;           // 最終的になってほしいフレーム数
	static bool isReverse = false; // 戻ってくる用のフラグ
	leftEarPosition_ = {};         // 最初のポジション
	if (firePos < -900 && !isShotFirstTime_) {
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
		leftEarSize_ = Math::Lerp(beginSize, endSize, Easing::Out(frame / endFrame));                             // 大きさを変える
	}
	if (isReverse) {
		if (frame++ > endFrame) {
			frame = endFrame;
			isReverse = false;
		}
		leftEarPosition_ = Math::Bezier(endPos, endPos + Vector3(-50.0f, 0.0f, 30.0f), {-1.53f,0.0f,0.0f}, Easing::InOut(frame / endFrame));
		leftEarSize_ = Math::Lerp(endSize, beginSize, Easing::In(frame / endFrame)); // 大きさを変える
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
