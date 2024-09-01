#include "TitleFont.h"
#include "Model.h"
#include "ViewProjection.h"
#include <cassert>
#include <numbers>

// 初期化
void TitleFont::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;//モデルを受け取る
	viewProjection_ = viewProjection;//ビュープロジェクションを受け取る
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	worldTransform_.translation_.z = -41.0f;//z軸を設定
	worldTransform_.rotation_.z = std::numbers::pi_v<float>;//z軸の角度を設定
	worldTransform_.rotation_.y = std::numbers::pi_v<float>;//y軸の角度を設定
	positionY = -1;//フォントの出る位置
}

// 更新
void TitleFont::Update() {
	float width = 1.0f;//振れ幅
	worldTransform_.translation_.y = width * sin(theta_) - positionY;//サイン波
	theta_ += std::numbers::pi_v<float> / 60.0f;//揺らすスピード
	worldTransform_.rotation_.y += 0.01f;//回転スピード
	worldTransform_.UpdateMatrix();//行列の更新
}

// 描画
void TitleFont::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
