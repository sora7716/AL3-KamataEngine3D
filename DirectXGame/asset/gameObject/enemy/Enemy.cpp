#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include "asset/gameObject/player/Player.h"
#include "asset/gameObject/score/Score.h"
#include "asset/math/Aithmetic.h"
using namespace std;
using namespace std::numbers;
Enemy::~Enemy() {}
// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection, Vector3 position) {
	assert(model);                           // Nullチェック
	model_ = model;                          // モデルを受け取る
	viewProjection_ = viewProjection;        // ビュープロジェクションを受け取る
	worldTransform_.Initialize();            // ワールドトランスフォームの初期化
	worldTransform_.translation_ = position; // 初期位置を設定
	firstPos = position;                     // 初期位置を設定
	// ステータスを設定
	actions_[0] = new EnemyStay();         // 止まっているとき
	actions_[1] = new EnemyLateralMove();  // 横移動のとき
	actions_[2] = new EnemyVerticalMove(); // 縦移動のとき
	actions_[0]->Initialize();             // 初期化
	status_ = actions_[0]->GetStatus();    // ステータスを得る
	
}


// 敵のステータスのメンバ関数ポインタの初期化
void (IEnemyState::*IEnemyState::EnemyPhaseTable[])(Enemy&) = {
    static_cast<void (IEnemyState::*)(Enemy&)>(&EnemyStay::Exce),
    static_cast<void (IEnemyState::*)(Enemy&)>(&EnemyLateralMove::Exce),
    static_cast<void (IEnemyState::*)(Enemy&)>(&EnemyVerticalMove::Exce),
};

// 更新
void Enemy::Update() {
	status_ = randomNum_;//ランダムな数字にする
	//  現在のフェーズを実行
	(actions_[status_]->*IEnemyState::EnemyPhaseTable[static_cast<size_t>(status_)])(*this);
	// 行列の更新
	worldTransform_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::Text("status:%d", status_);
	ImGui::End();
#endif // _DEBUG
}

// 描画
void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// 衝突したとき
void Enemy::OnCollision() {}

// 止まっているとき
void Enemy::StatusStay() { worldTransform_.rotation_ += Vector3(kRot, kRot, kRot); }

// 横移動しているとき
void Enemy::StatusLateralMove() {
	worldTransform_.rotation_ += Vector3(kRot, kRot, kRot);
	static float width = 1.0f;      // 振れ幅
	static float theta = 1.0f;      // 角度
	if (width < 10) {
		width += 0.01f; // 振れ幅をだんだん増やす
	}
	worldTransform_.translation_.x = width * std::sin(theta) - firstPos.x; // サイン波
	theta += pi_v<float> / 120.0f;                                          // 揺らすスピード
}

// 縦移動
void Enemy::StatusVerticalMove() {
	worldTransform_.rotation_ += Vector3(kRot, kRot, kRot);
	static float width = 1.0f;      // 振れ幅
	static float theta = 1.0f;      // 角度
	if (width < 10) {
		width += 0.01f; // 振れ幅をだんだん増やす
	}
	worldTransform_.translation_.y = width * std::sin(theta) + firstPos.y; // サイン波
	theta += pi_v<float> / 120.0f;                                          // 揺らすスピード
}

// ワールド座標のゲッター
Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

// AABBのゲッター
AABB Enemy::GetAABB() {
	Vector3 worldPosition = GetWorldPosition();
	AABB aabb;
	aabb.min = {worldPosition.x - kWidth / 2.0f, worldPosition.y - kHeight / 2.0f, worldPosition.z - kDepth / 2.0f};
	aabb.max = {worldPosition.x + kWidth / 2.0f, worldPosition.y + kHeight / 2.0f, worldPosition.z + kDepth / 2.0f};
	return aabb;
}

// 座標のセッター
void Enemy::SetPosition(Vector3 position) { worldTransform_.translation_ = position; }

// 親のセッター
void Enemy::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

// 敵の状態のセッター
void Enemy::SetStatus(int randomNum) { randomNum_ = randomNum; }
