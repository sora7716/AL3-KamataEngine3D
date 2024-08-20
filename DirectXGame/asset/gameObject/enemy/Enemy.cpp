#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Aithmetic.h"
#include <cassert>

// デストラクタ
Enemy::~Enemy() {
	// 削除
	delete model_;
}

// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const uint32_t& texture, const Vector3& position) {

	assert(model);                           // NULLチェック
	model_ = model;                          // モデルを代入
	viewProjection_ = viewProjection;        // ビュープロジェクションを代入
	worldTransform_.Initialize();            // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position; // 初期座標の設定
	texture_ = texture;                      // テクスチャハンドル
}

// staticで宣言したメンバ関数ポインタテーブルの実態
void (Enemy::*Enemy::EnemyPhaseTable[])() = {
    &Enemy::ApproachUpdate, // 要素番号0_接近
    &Enemy::LeaveUpdate,    // 要素番号1_離脱
};

// 更新
void Enemy::Update() {
	
	//現在のフェーズの関数を実行
	(this->*EnemyPhaseTable[static_cast<size_t>(phase_)])();

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	// 敵
	model_->Draw(worldTransform_, *viewProjection_, texture_);
}

// 接近中の更新
void Enemy::ApproachUpdate() {
	// 敵の動くスピード
	Vector3 velocity{0, 0, -kCharacterSpeed};
	// 移動(ベクトル加算)
	worldTransform_.translation_ += velocity;
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

// 離脱中の更新
void Enemy::LeaveUpdate() {
	// 敵の動くスピード
	Vector3 velocity{-kCharacterSpeed, kCharacterSpeed, -kCharacterSpeed};
	// 移動(ベクトル加算)
	worldTransform_.translation_ += velocity;
}
