#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
//#include "imgui.h"
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
	actions_[0]->Initialize();                // 接近の初期化
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

	//ImGui::Text("%d",phase_);

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


//プレイヤーのセッター
void Enemy::SetPlayer(Player* player, IEnemyState::Phase phase) { actions_[static_cast<int>(phase)]->player_ = player; }

// ワールドポジションのゲッター
Vector3 Enemy::GetWorldPosition() {
//ワールド座標を入れる変数
	Vector3 worldPos;
//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
