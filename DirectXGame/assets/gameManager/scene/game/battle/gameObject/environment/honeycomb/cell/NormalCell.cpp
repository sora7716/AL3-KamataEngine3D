#include "NormalCell.h"

// 初期化
void NormalCell::Initialize(Model* model, ViewProjection* viewProjection) { BaseCell::Initialize(model, viewProjection); }

// 更新
void NormalCell::Update() { 
	BaseCell::Update(); }

// 描画
void NormalCell::Draw() { BaseCell::Draw(); }

// 衝突したら
void NormalCell::OnCollision(bool isHit) { BaseCell::OnCollision(isHit); }
