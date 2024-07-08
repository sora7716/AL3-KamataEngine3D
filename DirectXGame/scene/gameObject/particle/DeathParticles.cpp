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
	for (int i = 0; i < kNumParticle; i++) {
		// 基本となる速度ベクトル
		Vector3 velocity = {kSpeed, 0.0f, 0.0f};
		// 回転角度を計算
		float angle = kAngleUnit * i;
		// Z回りの回転行列
		Matrix4x4 matrixRotate = Math::MakeRotateZMatrix(angle);
		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Math::Transform(velocity, matrixRotate);
		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	}
}

// フェードアウト
void DeathParticles::FadeOut() {
	color_.w = (1.0f - counter_);
	color_.w = std::clamp(color_.w, 0.0f, 1.0f);
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
}
