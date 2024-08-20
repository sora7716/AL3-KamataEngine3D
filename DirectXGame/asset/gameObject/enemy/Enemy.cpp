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

// 更新
void Enemy::Update() {
	//敵の動くスピード
	Vector3 velocity{0, 0, -kCharacterSpeed};
	worldTransform_.translation_ += velocity;
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() {
	// 敵
	model_->Draw(worldTransform_, *viewProjection_, texture_);
}
