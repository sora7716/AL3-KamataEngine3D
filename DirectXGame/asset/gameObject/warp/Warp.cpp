#include "Warp.h"
#include <cassert>
#include "Model.h"
#include "ViewProjection.h"

//初期化
void Warp::Initialize(Model* model, ViewProjection* viewProjection){ 
	assert(model);//nullチェック
	model_ = model; //モデルを受け取る
	viewProjection_=viewProjection;//ビュープロジェクションを受け取る
	worldTransform_.Initialize();//ワールドトランスフォームのゲッター
}

//更新
void Warp::Update() { worldTransform_.UpdateMatrix(); }

//描画
void Warp::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
