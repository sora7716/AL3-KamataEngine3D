#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Aithmetic.h"
#include <cassert>

// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const uint32_t& texture, const Vector3& position) {

	assert(model);                           // NULLチェック
	model_ = model;                          // モデルを代入
	viewProjection_ = viewProjection;        // ビュープロジェクションを代入
	worldTransform_.Initialize();            // ワールドトランスフォームを初期化
	worldTransform_.translation_ = position; // 初期座標の設定
	texture_ = texture;                      // テクスチャハンドル
	action_[0] = new EnemeyApproach();
	action_[1] = new EnemeyLeave();
}

// 更新
void Enemy::Update() {
	// 現在のフェーズを算出
	phase_ = action_[phase_]->GetPhase();
	//現在のフェーズを実行
	action_[phase_]->Exce(worldTransform_);
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	// 敵
	model_->Draw(worldTransform_, *viewProjection_, texture_);
}
