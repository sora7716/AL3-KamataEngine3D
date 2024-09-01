#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include "asset/gameObject/player/Player.h"
#include "asset/scene/GameScene.h"
#include <cassert>
#include <numbers>

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {}

// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);                           // NULLチェック
	model_ = model;                          // モデルを代入
	viewProjection_ = viewProjection;        // ビュープロジェクションを代入
	worldTransform_.Initialize();            // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position; // 初期座標の設定
	worldTransform_.rotation_.x = -std::numbers::pi_v<float> / 2.0f;
	actions_[0] = new EnemeyApproach(); // 接近
	actions_[1] = new EnemeyLeave();    // 離脱
	actions_[0]->Initialize();          // 接近の初期化
	phase_ = actions_[0]->GetPhase();
	actions_[1]->SetFirstPosition(position); // 最初の位置をセット
	// bulletModel_ = Model::Create();          // 弾のモデルを生成
	//  発射タイマーを初期化
	fireTimer_ = kFireInterval;
}

// メンバ関数ポンインタの初期化
void (IEnemyState::*IEnemyState::EnemyPhaseTable[])(WorldTransform&) = {
    static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemeyApproach::Exce), static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemeyLeave::Exce)};

// 更新
void Enemy::Update() {
	// 現在のフェーズを算出
	phase_ = actions_[phase_]->GetPhase();
	actions_[phase_]->SetPhase(phase_);
	// 現在のフェーズを実行
	(actions_[phase_]->*IEnemyState::EnemyPhaseTable[static_cast<size_t>(phase_)])(worldTransform_);

	// 発射タイマーカウントダウン
	fireTimer_--;
	// 指定時間に達した
	if (fireTimer_ <= 0 && phase_ == static_cast<int>(IEnemyState::Phase::Approach)) {
		// 弾を発射
		Fire();
		// 発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}

#ifdef _DEBUG
	ImGui::Begin("enemyGame");
	ImGui::Text("%d", phase_);
	ImGui::Text("%f", worldTransform_.translation_.y);
	ImGui::End();
#endif // DEBUG

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	// 敵
	model_->Draw(worldTransform_, *viewProjection_);
}

// タイトル用の初期化
void Enemy::TitleInitialize(Model* model, ViewProjection* viewProjection, const Vector3& position, const Vector3& angle) {
	assert(model);
	model_ = model;                                                  // モデルを受け取る
	viewProjection_ = viewProjection;                                // ビュープロジェクションを設定
	worldTransform_.Initialize();                                    // ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;                         // 位置の設定
	worldTransform_.rotation_ = angle;                               // アングルの設定
	worldTransform_.rotation_.x = -std::numbers::pi_v<float> / 2.0f; // 角度の設定
}

// タイトル用の更新
void Enemy::TitleUpdate() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

// 衝突を検出したら呼び出されるコールバック関数
void Enemy::OnCollision(int &kill) { 
	isDead_ = true; 
	kill++;
}

// 攻撃
void Enemy::Fire() {
	// Nullチェック
	assert(player_);
	Vector3 playerWorldPos = player_->GetWorldPosition();      // プレイヤーのワールド座標
	Vector3 enemyWorldPos = GetWorldPosition();                // 敵のワールド座標
	Vector3 subtractVector = playerWorldPos - enemyWorldPos;   // 差分ベクトルを求める( ゴールポジション - スタートポジション )
	Vector3 normalizeVector = Math::Normalize(subtractVector); // ベクトルを正規化
	// 弾の速度
	Vector3 velocity(normalizeVector * kBulletSpeed); // ベクトルの長さを、速さに合わせる

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = Math::TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(gameScene_->GetEnemyBulletModel(), worldTransform_.translation_, velocity);

	// 弾を登録
	gameScene_->AddEnemyBullet(newBullet);
}

// プレイヤーのセッター
void Enemy::SetPlayer(Player* player) { player_ = player; }

// AABBのゲッター
AABB Enemy::GetAABB() {
	Vector3 worldPosition = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPosition.x - kWidth / 2.0f, worldPosition.y - kHeight / 2.0f, worldPosition.z - kDepth / 2.0f};
	aabb.max = {worldPosition.x + kWidth / 2.0f, worldPosition.y + kHeight / 2.0f, worldPosition.z + kDepth / 2.0f};
	return aabb;
}

// ワールドポジションのゲッター
Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

// 親となるワールドトランスフォームをセット
void Enemy::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

// ゲームシーンのセッター
void Enemy::SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

// 死亡フラグのゲッター
bool Enemy::IsDead() const { return isDead_; }
