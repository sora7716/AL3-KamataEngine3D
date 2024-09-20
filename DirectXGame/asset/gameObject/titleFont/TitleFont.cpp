#include "TitleFont.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
#include "input/Input.h"
#include <cassert>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std::numbers;

// 初期化
void TitleFont::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);                          // NULLチェック
	model_ = model;                         // モデルを受け取る
	viewProjection_ = viewProjection;       // ビュープロジェクションを受け取る
	worldTransform_.Initialize();           // ワールドトランスフォームの初期化
	worldTransform_.translation_.z = 15.0f; // z座標を宣言
	worldTransform_.translation_.y = 17.0f;  // y座標を宣言
	frame_ = 0.0f;                          // フレームの初期化
}

// 更新
void TitleFont::Update() {
#ifdef _DEBUG
	ImGui::Begin("TitleFont");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::Checkbox("isSelectGameStart", &isSelectGameStart_);
	ImGui::Checkbox("isGameStartAnimation", &isGameStartAnimation_);
	ImGui::Text("stayTime:%f", stayTime_);
	ImGui::Checkbox("isBack", &isBack_);
	ImGui::Text("frame:%f", frame_);
	ImGui::End();
#endif // _DEBUG

	if (isSelectGameStart_) {
		isBack_ = true;
		stayTime_ = 120.0f;
		isSelectGameStart_ = false;
	} 
	if (stayTime_ > 0.0f) {
		stayTime_--;
		frame_ = 0.0f;
	}
	MoveFont();
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void TitleFont::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// ゲームスタートを選択したかのフラグのセッター
void TitleFont::SetIsSelectGameStart(bool isSelectGameStart) { isSelectGameStart_ = isSelectGameStart; }

// フォントの動き
void TitleFont::MoveFont() {
	static float begin = worldTransform_.translation_.y; // 最初の位置
	float end = 2.8f;                                    // 最後の位置
	float endFrame = 60;
	if (frame_++ > endFrame) {
		if (isPut) {
			frame_ = 0.0f;
			isPut = false;
		} else if (isBack_) {
			frame_ = 0.0f;
			isBack_ = false;
			isGameStartAnimation_ = true;
		}
	}
	if (isPut) {
		worldTransform_.translation_.y = Math::Lerp(begin, end, Easing::OutBounce(frame_ / endFrame));
	} else if (isBack_ && stayTime_ <= 0.0f) {
		worldTransform_.translation_.y = Math::Lerp(end, begin, Easing::InBack(frame_ / endFrame));
	}
}
