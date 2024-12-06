#include "IModel.h"
#include <cassert>
#include <string>

#pragma region インターフェース
// 初期化
void IModel::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

// 更新
void IModel::Update() { worldTransform_.UpdateMatrix(); }

// 描画
void IModel::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// デバックテキスト
void IModel::DebugText(const char* label) {
	(void)label;
#ifdef _DEBUG
	std::string imGuiLabel = (std::string)label + ".size";
	ImGui::DragFloat3(imGuiLabel.c_str(), &worldTransform_.scale_.x, 0.1f, 0.0f, 3.0f);
	imGuiLabel = (std::string)label + ".rotate";
	ImGui::DragFloat3(imGuiLabel.c_str(), &worldTransform_.rotation_.x, 0.1f);
	imGuiLabel = (std::string)label + ".translate";
	ImGui::DragFloat3(imGuiLabel.c_str(), &worldTransform_.translation_.x, 0.1f);
	imGuiLabel = (std::string)label + ".cycle";
	ImGui::SliderInt(imGuiLabel.c_str(), &cycle_, 1, 100);
	imGuiLabel = (std::string)label + ".amplitude";
	ImGui::SliderFloat(imGuiLabel.c_str(), &amplitude_, 0.0f, 10.0f);
#endif // DEBUG
}

// 親子付け
void IModel::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

// アニメーションに使用する変数の初期化
void IModel::InitializeAnimation() {
	// パラメーターの初期化
	floatingParameter_ = 0.0f;
	// 振幅数の初期化
	amplitude_ = 0.5f;
	// サイクル(どれくらいの感覚で動くか)
	cycle_ = 40;
	// 回転アングル
	angleTimer_ = 0.0f;
}

// 浮遊ギミックの更新
float IModel::UpdateFloatingGimmick() {
	float result = {};
	// 360度(2π)をサイクル分割る
	const float step = 2.0f * pi_f / cycle_;
	// パラメーターを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, wave_);
	// 浮動を座標に反映
	result = std::sin(floatingParameter_) * amplitude_;
	return result;
}

// 三角波を使用したギミックの更新
float IModel::UpdateTriangleGimmick() {
	float result = {};
	// 360度(2π)をサイクル分割る
	const float step = 2.0f * pi_f / cycle_;
	// パラメーターを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, wave_);
	// 浮動を座標に反映
	result = std::asin(std::sin(floatingParameter_)) * amplitude_;
	return result;
}

// サイン波と線形補間を利用したアニメーション
float IModel::LerpAnimation(const EasingMode& mode) {
	float result = 0.0f;
	result = Math::AngleLerp(startAngle_, endAngle_, mode, motionTime_, angleTimer_);
	return result;
}

// 三角波と線形補間を利用したアニメーション
float IModel::TriangleLerpAnimation(const EasingMode& mode) {
	float result = 0.0f;
	result = Math::TriangleAngleLerp(startAngle_, endAngle_, mode, motionTime_, angleTimer_);
	return result;
}

// 角度の線形補間
float IModel::AngleLerpAnimation(const EasingMode& mode) {
	float result = 0.0f;
	result = Math::Lerp(startAngle_, endAngle_, mode, motionTime_, angleTimer_);
	return result;
}

// ノコギリ波
float IModel::Sawtooth(float interval) {
	float result = {};
	// 360度(2π)をサイクル分割る
	const float step = interval / cycle_;
	// パラメーターを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, interval);
	// 浮動を座標に反映
	result = floatingParameter_ * amplitude_;
	return result;
}

// ワールドトランスフォームのゲッター
const WorldTransform& IModel::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

const Vector3 IModel::GetWorldPos(){
	return {
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	};
}

AABB IModel::GetAABB(){
	Vector3 worldpos = GetWorldPos();
	AABB aabb;
	aabb.min = { worldpos.x - kWidth_ / 2.0f, worldpos.y - kHeight_ / 2.0f, worldpos.z - kDepth_ / 2.0f };
	aabb.max = { worldpos.x + kWidth_ / 2.0f, worldpos.y + kHeight_ / 2.0f, worldpos.z + kDepth_ / 2.0f };
	return aabb;
}

#pragma endregion