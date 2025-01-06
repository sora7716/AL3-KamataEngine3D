#include "BaseCell.h"

//デストラクタ
BaseCell::~BaseCell() { delete hexagon_; }

// 初期化
void BaseCell::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	hexagon_ = new Hexagon();
	hexagon_->Initialize(viewProjection, {.size = worldTransform_.scale_, .rotation = worldTransform_.rotation_, .center = worldTransform_.translation_});
}

// 更新
void BaseCell::Update() {
	worldTransform_.UpdateMatrix();
	hexagon_->Update();
}

// 描画
void BaseCell::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// 衝突したら
void BaseCell::OnCollision(bool isHit) {
	isHit_ = isHit;
	hexagon_->OnCollision(isHit_);
}

// スケールのセッター
void BaseCell::SetScale(const Vector3 scale) { worldTransform_.scale_ = scale; }

// 回転のセッター
void BaseCell::SetRotate(const Vector3 rotate) { worldTransform_.rotation_ = rotate; }

// 平行移動のセッター
void BaseCell::SetTranslate(const Vector3 translate) { worldTransform_.translation_ = translate; }

// ワイヤーモデルゲッター
Hexagon* BaseCell::GetWireFrame() {
	return hexagon_; 
}

// ワイヤーモデルのセッター
void BaseCell::SetWireModel(Hexagon* hexagon) { hexagon_ = hexagon; }

//親子づけ
void BaseCell::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
