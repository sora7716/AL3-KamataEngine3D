#include "TitleFont.h"
#include "Model.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"
#include <cassert>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std::numbers;


//初期化
void TitleFont::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);//NULLチェック
	model_ = model;//モデルを受け取る
	viewProjection_ = viewProjection;//ビュープロジェクションを受け取る
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	worldTransform_.rotation_.y = pi_v<float> / 2.0f;//角度を設定
}

//更新
void TitleFont::Update() { 
#ifdef _DEBUG
	ImGui::Begin("TitleFont");
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	//行列の更新
	worldTransform_.UpdateMatrix(); 
}

//描画
void TitleFont::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
