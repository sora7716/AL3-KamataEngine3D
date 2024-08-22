#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
#include <cassert>

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {
	for (auto bullet : actions_[phase_]->GetBullet()) {
		delete bullet; // 弾を削除
	}
	actions_[phase_]->GetBullet().clear(); // 弾のあった配列も削除
}

// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const uint32_t& texture, const Vector3& position) {

	assert(model);                           // NULLチェック
	model_ = model;                          // モデルを代入
	viewProjection_ = viewProjection;        // ビュープロジェクションを代入
	worldTransform_.Initialize();            // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position; // 初期座標の設定
	texture_ = texture;                      // テクスチャハンドル
	actions_[0] = new EnemeyApproach();       // 接近
	actions_[1] = new EnemeyLeave();          // 離脱
	//初期化
	for (auto action : actions_) {
		action->Initialize();
	}
}

// メンバ関数ポンインタの初期化
void (IEnemyState::*IEnemyState::EnemyPhaseTable[])(WorldTransform&) = {
    static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemeyApproach::Exce),
	static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemeyLeave::Exce)
};

// 更新
void Enemy::Update() {

	// 現在のフェーズを算出
	phase_ = actions_[phase_]->GetPhase();
	// 現在のフェーズを実行
	(actions_[phase_]->*IEnemyState::EnemyPhaseTable[static_cast<size_t>(phase_)])(worldTransform_);

	// 弾の更新
	for (auto bullet : actions_[phase_]->GetBullet()) {
		if (bullet) {
			bullet->Update();
		}
	}

	//デスフラグが立った弾を削除
	actions_[phase_]->GetBullet().remove_if([](EnemyBullet* bullet) {
		if (bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
		}
		return false;
	});

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	// 敵
	model_->Draw(worldTransform_, *viewProjection_, texture_);

	// 弾
	for (auto bullet : actions_[phase_]->GetBullet()) {
		if (bullet) {
			bullet->Draw(*viewProjection_);
		}
	}
}
