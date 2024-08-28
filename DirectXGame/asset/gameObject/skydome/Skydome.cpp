#include "Skydome.h"
#include <cassert>

//スカイドームの初期化処理
void Skydome::Initialize(Model* model, ViewProjection* viewProjection) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}

//スカイドームの更新処理
void Skydome::Update() {

}

//スカイドームの描画処理
void Skydome::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_); 
}
