#include "Warp.h"
#include <cassert>
#include "Model.h"
#include "ViewProjection.h"
#include <numbers>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
using namespace std::numbers;


//初期化
void Warp::Initialize(Model* model, ViewProjection* viewProjection){ 
	assert(model);//nullチェック
	model_ = model; //モデルを受け取る
	viewProjection_=viewProjection;//ビュープロジェクションを受け取る
	worldTransform_.Initialize();//ワールドトランスフォームのゲッター
	worldTransform_.translation_.y = 1300;//場所
	worldTransform_.rotation_.z = pi_v<float> / 2.0f;//角度
	size_ = 9.0f;//サイズ
}

//更新
void Warp::Update() { 
	worldTransform_.scale_ = {size_, size_, size_};//サイズを上書き
	#ifdef _DEBUG
	ImGui::Begin("warp");
	ImGui::DragFloat("scale", &size_, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	worldTransform_.UpdateMatrix(); 
}

//描画
void Warp::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// 親子関係を築づく
void Warp::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
