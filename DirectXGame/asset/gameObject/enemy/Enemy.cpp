#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

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
	actions_[0] = new EnemyStay();        // 止まっているとき
	actions_[1] = new EnemyLateralMove(); // 動いて切るとき
	actions_[0]->Initialize();            // 初期化
	status_ = actions_[0]->GetStatus();   // ステータスを得る
}
// 敵のステータスのメンバ関数ポインタの初期化
void (IEnemyState::*IEnemyState::EnemyPhaseTable[])(Enemy&) = {
    static_cast<void (IEnemyState::*)(Enemy&)>(&EnemyStay::Exce),
    static_cast<void (IEnemyState::*)(Enemy&)>(&EnemyLateralMove::Exce),
};

// 更新
void Enemy::Update() {

	// 現在のステータスの算出
	//status_ = actions_[(int)status_]->GetStatus();
	// 現在のステータスに上書き
	//actions_[(int)status_]->SetStatus(status_);
	// 現在のフェーズを実行
	(actions_[status_]->*IEnemyState::EnemyPhaseTable[static_cast<size_t>(status_)])(*this);
	// 行列の更新
	worldTransform_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

}

// 描画
void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_); 
}

//衝突したとき
void Enemy::OnCollision() { 
	worldTransform_.translation_.x += 5.0f;
}

// 止まっているとき
void Enemy::StatusStay() {
	const int kChangeSecond = 120;
	static int chageTime = kChangeSecond; // n秒間だけまつ
	if (chageTime > 0) {
		chageTime--;
	} else {
		isStatusChange_ = true; // 状態を変更
		chageTime = kChangeSecond; // 時間を再設定
	}
}

// 横移動しているとき
void Enemy::StatusLateralMove() {
	const int kChangeSecond = 500;//切り替えまでの時間
	static float width = 1.0f;// 振れ幅
	static float theta = 1.0f;// 角度
	if (width < 10) {
		width += 0.01f;//振れ幅をだんだん増やす
	}
	worldTransform_.translation_.x = width * std::sin(theta) - firstPos.x; // サイン波
	theta += pi_v<float> / 60.0f;// 揺らすスピード

	static int chageTime = kChangeSecond;// n秒間だけまつ
	if (chageTime > 0) {
		chageTime--;
	} else {
		isStatusChange_ = true; // 状態を変更
		chageTime = kChangeSecond; // 時間を再設定
		width = 1.0f;//振れ幅を再設定
		firstPos = worldTransform_.translation_ * -1.0f;
	}
#ifdef _DEBUG
	ImGui::Text("%d", chageTime);
#endif // _DEBUG

}

// ステータスが変わったかどうか
bool Enemy::IsStatusChange() { return isStatusChange_; }

// ステータスが変わったかどうかのセッター
void Enemy::SetIsStatusChange(bool isStatusChange) {
	isStatusChange_ = isStatusChange; 
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

//親のセッター
void Enemy::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
