#include "StaffModel.h"

//初期化
void StaffModel::Initialize(Model* model, ViewProjection* viewProjection) { 
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.5f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {pi_f, 0.0f, 0.0f};
	//worldTransform_.scale_ = {0.0f, 0.0f, 0.0f};
}

//更新
void StaffModel::Update() { IModel::Update(); }

//デバックテキスト
void StaffModel::DebugText() { IModel::DebugText("staff"); }

//描画
void StaffModel::Draw() { IModel::Draw(); }

//通常
void StaffModel::BehaviorRootUpdate() {}

//打撃
void StaffModel::BehaviorBlowUpdate() {}
