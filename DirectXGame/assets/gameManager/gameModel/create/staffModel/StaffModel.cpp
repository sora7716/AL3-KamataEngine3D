#include "StaffModel.h"

//初期化
void StaffModel::Initialize(Model* model, ViewProjection* viewProjection) { 
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.5f, 0.0f, 0.0f};
	worldTransform_.rotation_ = {pi_f, 0.0f, 0.0f};
}

//更新
void StaffModel::Update() {
	IPlayerModel::Update();
	IModel::Update(); 
}

//デバックテキスト
void StaffModel::DebugText() { IModel::DebugText("staff"); }

//描画
void StaffModel::Draw() { IModel::Draw(); }

//通常状態の初期化
void StaffModel::BehaviorRootReset() { 
	IPlayerModel::BehaviorRootReset();
	worldTransform_.scale_ = {};
}

//通常
void StaffModel::BehaviorRootUpdate() { 
	worldTransform_.scale_ = {0.0f, 0.0f, 0.0f};
}

//打撃
void StaffModel::BehaviorBlowUpdate() { worldTransform_.scale_ = {1.0f, 1.0f, 1.0f}; }

//ダッシュ
void StaffModel::BehaviorDashUpdate() { worldTransform_.scale_ = {0.0f, 0.0f, 0.0f}; }
