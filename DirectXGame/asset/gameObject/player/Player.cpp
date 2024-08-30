#include "Player.h"
#include "Model.h"
#include "asset/math/Math.h"
#include "input/Input.h"
#include "asset/gameObject/player/bullet/PlayerBullet.h"
#include "asset/scene/GameScene.h"
#include <cassert>

// コンストラクタ
Player::Player() {}

// デストラクタ
Player::~Player() {}

// 初期化
void Player::Initialize(Model* model, ViewProjection* viewProjection, uint32_t texture, Vector3 position) {
	assert(model);
	model_ = model;                          // モデル
	viewProjection_ = viewProjection;        // ビュープロジェクション
	texture_ = texture;                      // テクスチャ
	worldTransform_.Initialize();            // ワールドトランスフォームの初期化
	worldTransform_.translation_ = position; // 初期位置
	input_ = Input::GetInstance();           // シングルインスタンス
}

// 更新
void Player::Update() {
	// デバックテキスト
	DebugText();

	// 攻撃
	Attack();

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_ += velocity_;

	// マトリックスの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, texture_); // プレイヤー
}

// 衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() {}

// 速度
void Player::SetVelocity(Vector3 velocity) { velocity_ = velocity; }

// ワールドポジションのゲッター
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

// 親となるワールドトランスフォームをセット
void Player::SetParent(const WorldTransform* parent) {
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
	parentTranslation_ = worldTransform_.parent_->translation_;
}

// ペアレントのトランスレイションのゲッター
Vector3 Player::GetParentTranslation() { return parentTranslation_; }

// ペアレントのローテションのゲッター
Vector3 Player::GetParentRotation() { return parentRotation_; }

// ゲームシーンのセッター
void Player::SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

#ifdef _DEBUG
#include "imgui.h"
void Player::DebugText() {
	ImGui::Begin("Player");
	ImGui::DragFloat3("playerPosition", &worldTransform_.translation_.x);
	ImGui::End();
}
#endif // _DEBUG

// 攻撃
void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾の速度
		Vector3 velocity{0, 0, kBulletSpeed};
		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = Math::TransformNormal(velocity, worldTransform_.matWorld_);
		// 生成
		PlayerBullet* newBullet = new PlayerBullet();
		// 初期化
		newBullet->Initialize(gameScene_->GetPlayerBulletModel(), GetWorldPosition(), velocity);
		// 弾を登録する
		gameScene_->AddPlayerBullet(newBullet);
	}
}

// 左へ移動
void Player::MoveLeft() { velocity_.x -= kCharacterSpeed; }

// 右へ移動
void Player::MoveRight() { velocity_.x += kCharacterSpeed; }

// 下へ移動
void Player::MoveDown() { velocity_.y -= kCharacterSpeed; }

// 上へ移動
void Player::MoveUp() { velocity_.y += kCharacterSpeed; }

// 右回り
void Player::RotateRight() { worldTransform_.rotation_.y -= kRotSpeed; }

// 左回り
void Player::RotateLeft() { worldTransform_.rotation_.y += kRotSpeed; }
