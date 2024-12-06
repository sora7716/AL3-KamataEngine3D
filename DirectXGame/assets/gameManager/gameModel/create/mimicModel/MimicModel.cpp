#include "MimicModel.h"
#include "assets/math/collision/Collision.h"

#pragma region ミミックのモデルインターフェース
// メンバ関数
// リセット
void (IMimicModel::* IMimicModel::ResetTable[])() {
	&BehaviorRootReset,
	&BehaviorBiteReset,
};
// 更新
void (IMimicModel::* IMimicModel::BehaviorTable[])() = {
	&BehaviorRootUpdate,
	&BehaviorBiteUpdate,
};

// リセット
void IMimicModel::Reset() {
	if (behaviorRequest_) {
		// 振る舞いを変更
		behavior_ = behaviorRequest_.value();
		// 更新
		(this->*ResetTable[(int)behavior_])();
		// 振る舞いをリセット
		behaviorRequest_ = std::nullopt;
	}
	if (actionTimer_ > 0.0f) {
		actionTimer_--;
	}
	else {
		if (behavior_ != IMimicModel::Behavior::kRoot) {
			behaviorRequest_ = IMimicModel::Behavior::kRoot;
		}
	}
}

// タイマーをリセット
void IMimicModel::SetActionTimer(float actionTime) {
	// 切り替えタイマーの設定
	actionTimer_ = actionTime;
}

// 更新
void IMimicModel::Update() {
	// リセット
	Reset();
	// 更新
	(this->*BehaviorTable[(int)behavior_])();
}

// ふるまいのセッター
void IMimicModel::SetBehaviorRequest(const Behavior& behavior) { behaviorRequest_ = behavior; }

// ふるまいのゲッター
MimicMode IMimicModel::GetBehavior() { return behavior_; }

// アクションタイマーのゲッター
float IMimicModel::GetActionTimer() { return actionTimer_; }

// 通常時の初期化
void IMimicModel::BehaviorRootReset() {
	// パラメーターの初期化
	floatingParameter_ = 0.0f;
	// 振幅数の初期化
	amplitude_ = 0.5f;
	// サイクル(どれくらいの感覚で動くか)
	cycle_ = 40;
	worldTransform_.rotation_ = {};
}

// 打撃時の初期化
void IMimicModel::BehaviorBiteReset() {
	// パラメーターの初期化
	floatingParameter_ = 1.0f;
	// 振幅数の初期化
	amplitude_ = 0.0f;
	// サイクル(どれくらいの感覚で動くか)
	cycle_ = 1;
}

#pragma endregion

#pragma region 蓋
// 初期化
void Lid::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	IModel::InitializeAnimation();
	startAngle_ = -45.0f;
	endAngle_ = 40.0f;
}

// 更新
void Lid::Update() {
	IMimicModel::Update();
	IModel::Update();
}

// デバックテキスト
void Lid::DebugText() { IModel::DebugText("Lid"); }

// 描画
void Lid::Draw() { IModel::Draw(); }
void Lid::BehaviorRootUpdate(){

}
void Lid::BehaviorBiteUpdate(){
	worldTransform_.rotation_.x = IModel::LerpAnimation(EasingMode::kOutQuad);
}
#pragma endregion

#pragma region 目
// 初期化
void Eye::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void Eye::Update() { 
	IMimicModel::Update();
	IModel::Update();
}

// デバックテキスト
void Eye::DebugText() { IModel::DebugText("eye"); }

// 描画
void Eye::Draw() { IModel::Draw(); }

void Eye::BehaviorRootUpdate(){

}
void Eye::BehaviorBiteUpdate(){

}
#pragma endregion

#pragma region 箱
// 初期化
void Box::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	IModel::InitializeAnimation();
	startAngle_ = 15.0f;
	endAngle_ = 0.0f;
}

// 更新
void Box::Update() {
	IMimicModel::Update();
	IModel::Update();
}

// デバックテキスト
void Box::DebugText() { IModel::DebugText("box"); }

// 描画
void Box::Draw() { IModel::Draw(); }
void Box::BehaviorRootUpdate(){
}
void Box::BehaviorBiteUpdate(){
	worldTransform_.rotation_.y = IModel::LerpAnimation(EasingMode::kOutBack);
}
#pragma endregion

#pragma region 舌
// 初期化
void Tongue::Initialize(Model* model, ViewProjection* viewProjection) { 
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, -0.6f, 1.0f};
	IModel::InitializeAnimation();
	startAngle_ = -110.0f;
	endAngle_ = 10.0f;
}

// 更新
void Tongue::Update() {
	IMimicModel::Update();
	IModel::Update();
}

// デバックテキスト
void Tongue::DebugText() { IModel::DebugText("tongue"); }

// 描画
void Tongue::Draw() { IModel::Draw(); }
void Tongue::BehaviorRootUpdate(){
}
void Tongue::BehaviorBiteUpdate(){
	worldTransform_.rotation_.x = IModel::LerpAnimation(EasingMode::kOutQuad);
}
#pragma endregion

#pragma region 歯(上)
// 初期化
void ToothUp::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void ToothUp::Update() {
	IMimicModel::Update();
	IModel::Update();
}

// デバックテキスト
void ToothUp::DebugText() { IModel::DebugText("toothUp"); }

// 描画
void ToothUp::Draw() { IModel::Draw(); }
void ToothUp::BehaviorRootUpdate(){

}
void ToothUp::BehaviorBiteUpdate(){

}
#pragma endregion

#pragma region 歯(下)
// 初期化
void ToothBottom::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }

// 更新
void ToothBottom::Update() {
	IMimicModel::Update();
	IModel::Update();
}

// デバックテキスト
void ToothBottom::DebugText() { IModel::DebugText("toothBottom"); }

// 描画
void ToothBottom::Draw() { IModel::Draw(); }
void ToothBottom::BehaviorRootUpdate(){

}
void ToothBottom::BehaviorBiteUpdate(){

}
#pragma endregion

#pragma region ミミックのモデル

// デストラクタ
MimicModel::~MimicModel() {
	for (auto part : parts_) {
		delete part;
	}
	parts_.clear();
}

// 初期化
void MimicModel::Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection) {
	parts_.resize((int)Parts::kPartsNum);
	parts_[(int)Parts::kBox] = new Box();                 // 箱
	parts_[(int)Parts::kLid] = new Lid();                 // 蓋
	parts_[(int)Parts::kEye] = new Eye();                 // 目
	parts_[(int)Parts::kToothUp] = new ToothUp();         // 上の歯
	parts_[(int)Parts::kToothBottom] = new ToothBottom(); // 下の歯
	parts_[(int)Parts::kTongue] = new Tongue();           // 舌
	// 初期化
	for (int i = 0; i < (int)Parts::kPartsNum; i++) {
		parts_[i]->Initialize(models[i], viewProjection);
	}
}

// 更新
void MimicModel::Update() {
	for (auto part : parts_) {
		part->Update();
#ifdef _DEBUG
		ImGui::Begin("mimic");
		part->DebugText();
		ImGui::End();
#endif // _DEBUG
	}
}

// 描画
void MimicModel::Draw() {
	for (auto part : parts_) {
		part->Draw();
	}
}

// 親子付け
void MimicModel::SetParent(const WorldTransform* parent) {
	// 箱<-親
	parts_[(int)Parts::kBox]->SetParent(parent);
	// 下の歯<-箱
	parts_[(int)Parts::kToothBottom]->SetParent(&parts_[(int)Parts::kBox]->GetWorldTransform());
	// 舌<-箱
	parts_[(int)Parts::kTongue]->SetParent(&parts_[(int)Parts::kBox]->GetWorldTransform());
	// 蓋<-親
	parts_[(int)Parts::kLid]->SetParent(parent);
	// 目<-蓋
	parts_[(int)Parts::kEye]->SetParent(&parts_[(int)Parts::kLid]->GetWorldTransform());
	// 上の歯<-蓋
	parts_[(int)Parts::kToothUp]->SetParent(&parts_[(int)Parts::kLid]->GetWorldTransform());
}
void MimicModel::SetBehavior(IMimicModel::Behavior behavior){
	for (int i = 0; i < parts_.size(); i++) {
		parts_[i]->SetBehaviorRequest(behavior);
	}
}
IMimicModel::Behavior MimicModel::GetBehavior(){
	return parts_[(int)Parts::kBox]->GetBehavior();
}
#pragma endregion