#include "HitEffect.h"
#include "cassert"
#include "algorithm"
#include"imgui.h"

void HitEffect::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	viewProjection_ = viewProjection;

	// ワールド変換データの初期化
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void HitEffect::Update() {

	if (!isFinished_) {
		return;
	}

	// ワールド変換データの更新
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}

	for (int32_t i = 0; i < kNumParticle; i++) {
		Vector3 velocity = {kSpeed, 0, 0};
		float angle = kAngleUnit * i;
		Matrix4x4 rotateMatrixZ = Math::MakeRotateZMatrix(angle);
		velocity = Math::Transform(velocity, rotateMatrixZ);

		worldTransforms_[i].translation_ += velocity; 
	}

	// カウンターを一フレーム文の秒数を進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の条件に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	color_.w = std::clamp(1.0f - (counter_ / kDuration), 0.0f, 1.0f);

	// 色変更オブジェクトに色に数値を設定する
	objectColor_.SetColor(color_);

	// 色変更オブジェクトをVRAMに転送
	objectColor_.TransferMatrix();
}

void HitEffect::Draw() {

	//終了なら何もしない
	if (isFinished_) {
		return;
	}

	//モデルの描画
	for (auto& WorldTransform : worldTransforms_) {

		model_->Draw(WorldTransform, *viewProjection_, &objectColor_);
	}
}


