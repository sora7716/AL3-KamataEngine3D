#include "BaseModel.h"
#include <cassert>

//初期化
void BaseModel::Initialize(ViewProjection* viewProjection, Model* model) { 
	viewProjection_ = viewProjection; 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
}

//更新
void BaseModel::Update() { worldTransform_.UpdateMatrix(); }

//描画
void BaseModel::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

//親のセッター
void BaseModel::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

// ワールドトランスフォームのゲッター
const WorldTransform* BaseModel::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return &worldTransform_;
}
