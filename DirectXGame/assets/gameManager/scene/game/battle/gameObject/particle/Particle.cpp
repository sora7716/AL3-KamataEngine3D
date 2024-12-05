#include "Particle.h"
#include "ViewProjection.h"
#include "Model.h"
#include "cassert"

//初期化
void Particle::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model; 
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	objectColor_.Initialize();
}

//更新
void Particle::Update() { 
	objectColor_.SetColor(color_);
	objectColor_.TransferMatrix();
	worldTransform_.UpdateMatrix(); 
}

//描画
void Particle::Draw() { model_->Draw(worldTransform_, *viewProjection_,&objectColor_); }
