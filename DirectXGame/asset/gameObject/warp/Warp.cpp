#include "Warp.h"
#include <cassert>

//初期化
void Warp::Initialize(Model* model, ViewProjection* viewProjection){ 
	model_ = model; 
	(void)viewProjection;
}

//更新
void Warp::Update() {}

//描画
void Warp::Draw() {}
