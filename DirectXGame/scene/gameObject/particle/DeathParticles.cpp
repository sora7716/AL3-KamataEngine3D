#include "DeathParticles.h"
#include "Model.h"
#include "calculate/Math.h"
#include "gameObject/player/Player.h"
#include <algorithm>
#include <cassert>
#define oneFrame 1.f / 60.f;
// コンストラクタ
DeathParticles::DeathParticles() {
	player_ = nullptr;
	viewProjection_ = nullptr;
	model_ = nullptr;
	textureHandle_ = 0u;
	isFinished_ = false;
	counter_ = 0.0f;
	objectColor_ = {};
	color_ = {};
}

// デストラクタ
DeathParticles::~DeathParticles() {}

// 初期化
void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, Vector3 position, uint32_t textureHandle) {
	// 値の代入
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	textureHandle_ = textureHandle;
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();            // ワールドトランスフォームの初期化
		worldTransform.translation_ = position; // ポジションの指定
	}
	objectColor_.Initialize();
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};

}

// 更新処理
void DeathParticles::Update() {
	// 終了だったら何もしない
	if (isFinished_) {
		return;
	}
	DestoryCount(); // パーティクルが消えるまでの時間を計測
	SettingSpeed(); // 速度ベクトルの設定
	FadeOut();      // フェードアウト
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix(); // 行列の更新
	}
}

// 描画処理
void DeathParticles::Draw() {
	// 終了だったら何もしない
	if (isFinished_) {
		return;
	}

	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_, textureHandle_, &objectColor_);
	}
}

//終了フラグのゲッター
bool DeathParticles::IsFinished() const { return isFinished_; }

//終了フラグのセッター」
void DeathParticles::SetIsFinished(bool isFinished) { isFinished_ = isFinished; }

//ポジションのセッター
void DeathParticles::SetPosition(const Vector3& position) {
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.translation_ = position;
	}
}

// パーティクルが消えるまでの時間を計測
void DeathParticles::DestoryCount() {
	// 1フレーム分秒数を進める
	counter_ += oneFrame;
	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}
}

// 移動ベクトルの設定
void DeathParticles::SettingSpeed() {
	const float kThetaUnit = 2.0f * pi_f / kNumParticle; // 経度の単位角度（360度を分割）
	const float kPhiUnit = pi_f / kNumParticle;          // 緯度の単位角度（180度を分割）
	Vector3 velocity = {0.0f, 0.0f, kSpeed};             // 初期ベクトルはZ方向の速度

	for (int i = 0; i < kNumParticle; ++i) {
		// 経度（theta）と緯度（phi）を計算
		float theta = kThetaUnit * i;            // 経度方向の角度 (0 ~ 2π)
		float phi = -pi_f / 2.0f + kPhiUnit * i; // 緯度方向の角度 (-π/2 ~ π/2)

		// 経度 (theta) で Y軸回りに回転
		Matrix4x4 matrixRotateY = Math::MakeRotateYMatrix(theta);
		// 緯度 (phi) で X軸回りに回転
		Matrix4x4 matrixRotateX = Math::MakeRotateXMatrix(phi);

		// 速度ベクトルに回転行列を適用してスフィア状の方向に飛ばす
		Vector3 rotatedVelocity = Math::Transform(velocity, matrixRotateX); // 緯度方向の回転を適用
		rotatedVelocity = Math::Transform(rotatedVelocity, matrixRotateY);  // 経度方向の回転を適用

		// 移動処理
		worldTransforms_[i].translation_ += rotatedVelocity;
	}
}

// フェードアウト
void DeathParticles::FadeOut() {
	color_.w = (1.0f - counter_);
	color_.w = std::clamp(color_.w, 0.0f, 1.0f);
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
}
