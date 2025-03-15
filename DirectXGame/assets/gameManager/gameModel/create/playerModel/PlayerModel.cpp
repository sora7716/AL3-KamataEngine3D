#include "PlayerModel.h"
#include "assets/gameManager/gameModel/create/staffModel/StaffModel.h"

#pragma region 頭
// 初期化
void Head::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
}

// 更新
void Head::Update() {
	// リセット
	Reset();
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Head::DebugText() { IModel::DebugText("head"); }

// 描画
void Head::Draw() { IModel::Draw(); }

// 通常
void Head::BehaviorRootUpdate() {}

// 打撃
void Head::BehaviorBlowUpdate() { 

}

#pragma endregion

#pragma region 体
// 初期化
void Body::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 0.2f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void Body::Update() {
	// リセット
	Reset();
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Body::DebugText() { IModel::DebugText("body"); }

// 描画
void Body::Draw() { IModel::Draw(); }

// 通常
void Body::BehaviorRootUpdate() { worldTransform_.translation_.y = UpdateFloatingGimmick(); }

// 打撃
void Body::BehaviorBlowUpdate() { 	
	worldTransform_.translation_.y = UpdateFloatingGimmick();
}

#pragma endregion

#pragma region 右腕
// 初期化
void RightArm::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.5f, 1.2f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void RightArm::Update() {
	// リセット
	Reset();
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void RightArm::DebugText() { IModel::DebugText("rightArm"); }

// 描画
void RightArm::Draw() { IModel::Draw(); }

// 通常行動用
void RightArm::BehaviorRootUpdate() {
	// アニメーションの更新
	worldTransform_.rotation_.x = UpdateTriangleGimmick();
}

// 打撃用
void RightArm::BehaviorBlowUpdate() {
	motionTime_ = 1.0f;
	startAngle_ = 160.0f;
	endAngle_ = 270.0f;
	worldTransform_.rotation_.x = TriangleLerpAnimation(EasingMode::kInSine);
}

#pragma endregion

#pragma region 左腕
// 初期化
void LeftArm::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {-0.5f, 1.2f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void LeftArm::Update() {
	// リセット
	Reset();
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void LeftArm::DebugText() { IModel::DebugText("leftArm"); }

// 描画
void LeftArm::Draw() { IModel::Draw(); }

// 通常行動用
void LeftArm::BehaviorRootUpdate() {
	// アニメーションの更新
	worldTransform_.rotation_.x = UpdateTriangleGimmick();
}

// 打撃用
void LeftArm::BehaviorBlowUpdate() {
	motionTime_ = 1.0f;
	startAngle_ = 160.0f;
	endAngle_ = 270.0f;
	worldTransform_.rotation_.x = TriangleLerpAnimation(EasingMode::kInSine);
}

#pragma endregion

#pragma region プレイヤーのモデル
// デストラクタ
PlayerModel::~PlayerModel() {
	for (auto part : parts_) {
		delete part;
	}
	parts_.clear();
}
// 初期化
void PlayerModel::Initialize(std::vector<Model*>&& models, ViewProjection* viewProjection) {
	// 配列の大きさを設定
	parts_.resize((int)Parts::kPartsNum);
	// 生成
	parts_[(int)Parts::kHead] = new Head();
	parts_[(int)Parts::kBody] = new Body();
	parts_[(int)Parts::kRightArm] = new RightArm();
	parts_[(int)Parts::kLeftArm] = new LeftArm();
	parts_[(int)Parts::kStaff] = new StaffModel();
	// 初期化
	worldTransform_.Initialize();
	// 初期化
	for (int i = 0; i < (int)Parts::kPartsNum; i++) {
		assert(models[i]);
		parts_[i]->Initialize(models[i], viewProjection);
	}
}
// 更新
void PlayerModel::Update() {
	worldTransform_.UpdateMatrix();
	for (auto iPalayerModel : parts_) {
		iPalayerModel->Update();
#ifdef _DEBUG
		ImGui::Begin("playerParts");
		iPalayerModel->DebugText();
		ImGui::End();
#endif // _DEBUG
	}
}

// 描画
void PlayerModel::Draw() {
	for (auto iPalayerModel : parts_) {
		iPalayerModel->Draw();
	}
}

// 親のセッター
void PlayerModel::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
	// 体<-Parent
	parts_[(int)Parts::kBody]->SetParent(&worldTransform_);
	// 頭<-体
	parts_[(int)Parts::kHead]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 右腕<-体
	parts_[(int)Parts::kRightArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 左腕<-体
	parts_[(int)Parts::kLeftArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	parts_[(int)Parts::kStaff]->SetParent(&parts_[(int)Parts::kLeftArm]->GetWorldTransform());
}

#pragma endregion

#pragma region プレイヤーのモデルインターフェース
// メンバ関数
// リセット
void (IPlayerModel::*IPlayerModel::ResetTable[])(){
    &BehaviorRootReset,
    &BehaviorBlowReset,
};
// 更新
void (IPlayerModel::*IPlayerModel::BehaviorTable[])() = {
    &BehaviorRootUpdate,
    &BehaviorBlowUpdate,
};

// リセット
void IPlayerModel::Reset() {
	if (behaviorRequest_) {
		// 振る舞いを変更
		behavior_ = behaviorRequest_.value();
		// 更新
		(this->*ResetTable[(int)behavior_])();
		// 振る舞いをリセット
		behaviorRequest_ = std::nullopt;
	}
	if (changeTimer_-- < 0.0f&&behavior_!=IPlayerModel::Behavior::kRoot) {
		behaviorRequest_ = IPlayerModel::Behavior::kRoot;
	}
	else if(changeTimer_ <= 0.0f) {
		changeTimer_ = 0.0f;
	}
}

//タイマーの設定
void IPlayerModel::ChangeTime() {
	// 切り替えタイマーの設定
	changeTimer_ = kMaxTimer_;
}

// 更新
void IPlayerModel::Update() {
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		behaviorRequest_ = IPlayerModel::Behavior::kBlow;
		// タイマーの設定
		ChangeTime();
	}
	ImGui::DragFloat("Timer", &changeTimer_);
	// 更新
	(this->*BehaviorTable[(int)behavior_])();
}

// 通常時の初期化
void IPlayerModel::BehaviorRootReset() {
	// パラメーターの初期化
	floatingParameter_ = 0.0f;
	// 振幅数の初期化
	amplitude_ = 0.5f;
	// サイクル(どれくらいの感覚で動くか)
	cycle_ = 40;
}

// 打撃時の初期化
void IPlayerModel::BehaviorBlowReset() {
	// パラメーターの初期化
	floatingParameter_ = 1.0f;
	// 振幅数の初期化
	amplitude_ = 0.0f;
	// サイクル(どれくらいの感覚で動くか)
	cycle_ = 1;
}
#pragma endregion
