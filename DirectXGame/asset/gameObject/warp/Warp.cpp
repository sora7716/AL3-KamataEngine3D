#include "Warp.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
#include <cassert>
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std::numbers;

// 初期化
void Warp::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                                    // nullチェック
	model_ = model;                                   // モデルを受け取る
	viewProjection_ = viewProjection;                 // ビュープロジェクションを受け取る
	worldTransform_.Initialize();                     // ワールドトランスフォームのゲッター
	worldTransform_.translation_.y = 1320;            // 場所
	worldTransform_.rotation_.z = pi_v<float> / 2.0f; // 角度
}

// 更新
void Warp::Update(bool isSpawn) {
	worldTransform_.scale_ = {size_, size_, size_}; // サイズを上書き
#ifdef _DEBUG
	ImGui::Begin("warp");
	ImGui::DragFloat("scale", &size_, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
	if (isSpawn) {
		Spawn(); // 登場させる
	} else {
		sizeEasing_ = 0.0f; // ゼロの設定
		isAlive_ = false;
	}
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Warp::Draw() {
	//生存フラグがtrueの時に表示
	if (isAlive_) {
		model_->Draw(worldTransform_, *viewProjection_);
	}
}

// 親子関係を築づく
void Warp::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

// サイズのセッター
void Warp::SetSize(float size) { size_ = size; }

// スポーン
void Warp::Spawn() {
	float begin = 0.0f;     // 最初のサイズ
	float end = 8.0f;       // 最後のサイズ
	float endFrame = 30.0f; // 最後のフレーム
	isAlive_ = true;
	if (sizeEasing_++ > endFrame) {
		sizeEasing_ = endFrame; // フレームを固定
		size_ = end;            // サイズを最後のやつに設定
	}
	size_ = Math::Lerp(begin, end, Easing::EaseOutElastic(sizeEasing_ / endFrame)); // 線形補間
}
