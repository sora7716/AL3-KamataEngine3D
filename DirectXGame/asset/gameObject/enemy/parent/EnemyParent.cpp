#include "EnemyParent.h"
#include "asset/gameObject/skydome/SkyDome.h"
#include <cstdlib>
#include <ctime>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void EnemyParent::Initialize() {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	srand(static_cast<uint32_t>(time(nullptr))); // エスランドを宣言
	randomNum_ = 1;
}

// 更新
void EnemyParent::Update(int score_) {
	if (score_ > 500) { // スコアが500に行ったら回転させる
		worldTransform_.rotation_.z += 0.1f * (float)randomNum_;
	}
	if (score_ > 1000 && rotateRandomTime_ < 0) { // スコア1000に行ったら
		isRotateRandom_ = true;                // 回転をランダムにする
	}
	if (isRotateRandom_) {
		isRotateRandom_ = false;                   // ランダムフラグをfalse
		rotateRandomTime_ = kRotateRandomInterval; // 時間を設定
	}
	if (rotateRandomTime_-- <= 0) {
		randomNum_ = rand() % 3 - 1; // ランダムな値を入れる
	}
	worldTransform_.translation_.z -= skyDome_->GetVelocityZ();
	// 行列の更新
	worldTransform_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("enemySpeed");
	ImGui::Checkbox("isRandom", &isRotateRandom_);
	ImGui::Text("timer:%d", rotateRandomTime_);
	ImGui::Text("randomNum:%d", randomNum_);
	ImGui::End();
#endif // _DEBUG
}

// 親クラスのセット
void EnemyParent::SetParent(const WorldTransform* parent) {
	// 親のセット
	worldTransform_, parent = parent;
}

// ワールドトランスフォームのゲッター
WorldTransform& EnemyParent::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// ポジションのセッター
void EnemyParent::SetPosition(Vector3 position) { worldTransform_.translation_ = position; }

// スカイドームの設定
void EnemyParent::SetSkyDome(SkyDome* skyDome) { skyDome_ = skyDome; }
