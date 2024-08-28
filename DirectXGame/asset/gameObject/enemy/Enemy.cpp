#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
// #include "imgui.h"
#include "asset/gameObject/player/Player.h"
#include <cassert>

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {
	for (auto bullet : bullets_) {
		delete bullet; // 弾を削除
	}
	bullets_.clear();    // 弾のあった配列も削除
	delete bulletModel_; // 弾のモデルの削除
}

// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const uint32_t& texture, const Vector3& position) {

	assert(model);                           // NULLチェック
	model_ = model;                          // モデルを代入
	viewProjection_ = viewProjection;        // ビュープロジェクションを代入
	worldTransform_.Initialize();            // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position; // 初期座標の設定
	texture_ = texture;                      // テクスチャハンドル
	actions_[0] = new EnemeyApproach();      // 接近
	actions_[1] = new EnemeyLeave();         // 離脱
	actions_[0]->Initialize();               // 接近の初期化
	bulletModel_ = Model::Create();          // 弾のモデルを生成
	// 発射タイマーを初期化
	fireTimer_ = kFireInterval;
}

// メンバ関数ポンインタの初期化
void (IEnemyState::*IEnemyState::EnemyPhaseTable[])(WorldTransform&) = {
    static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemeyApproach::Exce), static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemeyLeave::Exce)};

// 更新
void Enemy::Update() {
	// 現在のフェーズを算出
	phase_ = actions_[phase_]->GetPhase();
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

	// デスフラグが立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
		}
		return false;
	});

	// 弾の更新
	for (auto bullet : bullets_) {
		if (bullet) {
			bullet->SetPlayer(player_);
			bullet->Update();
		}
	}

	// ImGui::Text("%d",phase_);

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	// 敵
	model_->Draw(worldTransform_, *viewProjection_, texture_);

	// 弾
	for (auto bullet : bullets_) {
		if (bullet) {
			bullet->Draw(*viewProjection_);
		}
	}
}

// 衝突を検出したら呼び出されるコールバック関数
void Enemy::OnCollision() {}

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
	newBullet->Initialize(bulletModel_, worldTransform_.translation_, velocity);

	// 弾を登録
	bullets_.push_back(newBullet);
}

// プレイヤーのセッター
void Enemy::SetPlayer(Player* player) { player_ = player; }

//AABBのゲッター
AABB Enemy::GetAABB(){
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

// 弾のリストを取得
const list<EnemyBullet*>& Enemy::GetBullet() const {
	// TODO: return ステートメントをここに挿入します
	return bullets_;
}