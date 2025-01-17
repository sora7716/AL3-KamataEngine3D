#include "PlayerModel.h"
#include "assets/gameManager/gameModel/create/staffModel/StaffModel.h"

#pragma region プレイヤーのモデルインターフェース
// メンバ関数
// リセット
void (IPlayerModel::*IPlayerModel::ResetTable[])(){&BehaviorRootReset, &BehaviorBlowReset, &BehaviorDashReset};
// 更新
void (IPlayerModel::*IPlayerModel::BehaviorTable[])() = {
    &BehaviorRootUpdate,
    &BehaviorBlowUpdate,
    &BehaviorDashUpdate,
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
	if (actionTimer_ > 0.0f) {
		actionTimer_--;
	} else {
		if (behavior_ != BehaviorMode::kRoot) {
			behaviorRequest_ = BehaviorMode::kRoot;
		}
	}
}

// タイマーをリセット
void IPlayerModel::SetActionTimer(float actionTime) {
	// 切り替えタイマーの設定
	actionTimer_ = actionTime;
}

// 更新
void IPlayerModel::Update() {
	// リセット
	Reset();
	// 更新
	(this->*BehaviorTable[(int)behavior_])();
}

// ふるまいのセッター
void IPlayerModel::SetBehaviorRequest(const Behavior& behavior) { behaviorRequest_ = behavior; }

// ふるまいのゲッター
BehaviorMode IPlayerModel::GetBehavior() { return behavior_; }

// アクションタイマーのゲッター
float IPlayerModel::GetActionTimer() { return actionTimer_; }

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
	// 振り上げをする時間
	angleTimer_ = 0.0f;
	// 加算する時間
	second_ = deltaTime;
	// 待機時間を開始するか
	isStartWait_ = false;
	// 待つ時間を計測する
	waitTime_ = 0.0;
	// angleTimerを加算するか
	isAngleTimerAdd_ = true;
	// イージングのモード
	easingMode_ = EasingMode::kInSine;
	// 周期
	motionTime_ = 0.3f;
	// 開始時のアングル
	startAngle_ = 300.0f;
	// 目標のアングル
	endAngle_ = 130.0f;
}
// ダッシュ時の初期化
void IPlayerModel::BehaviorDashReset() {}

void IPlayerModel::BehaviorRootUpdate() {}

void IPlayerModel::BehaviorBlowUpdate() {}

void IPlayerModel::BehaviorDashUpdate() {}

// 打撃時の切り替えタイマー
void IPlayerModel::BlowChangeTimer() {
	// 振り上げきったら
	if (angleTimer_ > motionTime_ + 0.2f && isAngleTimerAdd_) {
		isAngleTimerAdd_ = false;
		isStartWait_ = true;
		second_ = 0.0f;
		easingMode_ = EasingMode::kInExpo;
	} else if (angleTimer_ <= 0.0f && !isAngleTimerAdd_) { // 降り下げきったら
		isAngleTimerAdd_ = true;
		second_ = 0.0f;
		isStartWait_ = true;
		easingMode_ = EasingMode::kInSine;
	}

	// 待機時間
	if (isStartWait_) {
		waitTime_ += deltaTime;
		if (waitTime_ >= kMaxBlowWaitTime) {
			isStartWait_ = false;
			waitTime_ = 0.0f;
			second_ = deltaTime;
		}
	}

	// フレームを加算するかどうか
	if (isAngleTimerAdd_) {
		angleTimer_ += second_;
	} else {
		angleTimer_ -= second_;
	}
}

#pragma endregion

#pragma region 髪
// 初期化
void Hair::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 0.026f, 0.0f};
}

// 更新
void Hair::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Hair::DebugText() { IModel::DebugText("hair"); }

// 描画
void Hair::Draw() { IModel::Draw(); }

// 通常
void Hair::BehaviorRootUpdate() {}

// 打撃
void Hair::BehaviorBlowUpdate() { 
	//worldTransform_.rotation_.y = Math::AngleLerp(360, 0, EasingMode::kInBack, 10, angleTimer_); 
}

// ダッシュ
void Hair::BehaviorDashUpdate() {}

#pragma endregion

#pragma region 眉毛
// 初期化
void EyeBrows::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	//worldTransform_.translation_ = {0.0f, 0.2f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void EyeBrows::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
// 描画
void EyeBrows::Draw() { IModel::Draw(); }

// デバックテキスト
void EyeBrows::DebugText() { IModel::DebugText("eyeBrows"); }

// 通常
void EyeBrows::BehaviorRootUpdate() {
	/*worldTransform_.rotation_ = {};
	worldTransform_.translation_.y = UpdateFloatingGimmick();*/
}

// 打撃
void EyeBrows::BehaviorBlowUpdate() {
	worldTransform_.rotation_ = {};
	worldTransform_.translation_.y = UpdateFloatingGimmick();
}

// ダッシュ
void EyeBrows::BehaviorDashUpdate() {
	worldTransform_.rotation_.x = 0.4f;
	worldTransform_.translation_.y = UpdateFloatingGimmick();
}

#pragma endregion

#pragma region 顔
// 初期化
void Face::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 0.5f, 0.0f};
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void Face::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Face::DebugText() { IModel::DebugText("face"); }

// 描画
void Face::Draw() { IModel::Draw(); }

// 通常行動用
void Face::BehaviorRootUpdate() {
	// アニメーションの更新
	//worldTransform_.rotation_.x = UpdateTriangleGimmick();
}

// 打撃用
void Face::BehaviorBlowUpdate() {
	IPlayerModel::BlowChangeTimer();
	worldTransform_.rotation_.x = AngleLerpAnimation(easingMode_);
}

// 打撃用の初期化
void Face::BehaviorBlowReset() {
	IPlayerModel::BehaviorBlowReset();
	angleTimer_ = 0.0f;
}

// ダッシュ
void Face::BehaviorDashUpdate() {
	motionTime_ = 1.0f;
	startAngle_ = 90.0f;
	endAngle_ = 45.0f;
	worldTransform_.rotation_.x = TriangleLerpAnimation(EasingMode::kNormal);
}

#pragma endregion

#pragma region 体
// 初期化
void Body::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	// worldTransform_.translation_ = {-0.5f, 1.2f, 0.0f};// 初期値
	worldTransform_.translation_ = {0.0f, 4.2f,-9.0f};// 調整しやすくするための値
	// アニメーションの初期化
	InitializeAnimation();
}

// 更新
void Body::Update() {
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void Body::DebugText() { IModel::DebugText("body"); }

// 描画
void Body::Draw() { IModel::Draw(); }

// 通常行動用
void Body::BehaviorRootUpdate() {
	// アニメーションの更新
	//worldTransform_.rotation_.x = UpdateTriangleGimmick();
}

// 打撃用
void Body::BehaviorBlowUpdate() {
	IPlayerModel::BlowChangeTimer();
	worldTransform_.rotation_.x = AngleLerpAnimation(easingMode_);
}

// 打撃用の初期化
void Body::BehaviorBlowReset() {
	IPlayerModel::BehaviorBlowReset();
	angleTimer_ = 0.0f;
}

// ダッシュ
void Body::BehaviorDashUpdate() {
	motionTime_ = 1.0f;
	startAngle_ = 90.0f;
	endAngle_ = 45.0f;
	worldTransform_.rotation_.x = TriangleLerpAnimation(EasingMode::kNormal);
}

#pragma endregion

#pragma region 左腕
void LeftArm::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LeftArm::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LeftArm::DebugText() { IModel::DebugText("leftArm"); }
void LeftArm::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 右腕
void RightArm::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void RightArm::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void RightArm::DebugText() { IModel::DebugText("rightArm"); }
void RightArm::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 左腿
void LeftLeg::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LeftLeg::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LeftLeg::DebugText() { IModel::DebugText("leftLeg"); }
void LeftLeg::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 左脛
void LeftThigh::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LeftThigh::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LeftThigh::DebugText() { IModel::DebugText("leftThigh"); }
void LeftThigh::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 右腿
void RightLeg::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void RightLeg::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void RightLeg::DebugText() { IModel::DebugText("rightLeg"); }
void RightLeg::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 右脛
void RightThigh::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void RightThigh::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void RightThigh::DebugText() { IModel::DebugText("rightThigh"); }
void RightThigh::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 服(上)
void UpperClothing::Initialize(Model* model, ViewProjection* viewProjection) { 
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 0.15f, 0.0f};
}
void UpperClothing::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void UpperClothing::DebugText() { IModel::DebugText("upperClothing"); }
void UpperClothing::Draw() { IModel::Draw(); }
#pragma endregion

#pragma region 服(下)
void LowerClothing::Initialize(Model* model, ViewProjection* viewProjection) { IModel::Initialize(model, viewProjection); }
void LowerClothing::Update() { // 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}
void LowerClothing::DebugText() { IModel::DebugText("lowerClothing"); }
void LowerClothing::Draw() { IModel::Draw(); }
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
	parts_[(int)Parts::kHair] = new Hair();
	parts_[(int)Parts::kEyeBrows] = new EyeBrows();
	parts_[(int)Parts::kFace] = new Face();
	parts_[(int)Parts::kBody] = new Body();
	parts_[(int)Parts::kLeftArm] = new LeftArm();
	parts_[(int)Parts::kRightArm] = new RightArm();
	parts_[(int)Parts::kLeftLeg] = new LeftLeg();
	parts_[(int)Parts::kLeftThigh] = new LeftThigh();
	parts_[(int)Parts::kRightLeg] = new RightLeg();
	parts_[(int)Parts::kRightThigh] = new RightThigh();
	parts_[(int)Parts::kUpperClothing] = new UpperClothing();
	parts_[(int)Parts::kLowerClothing] = new LowerClothing();
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
	//体<-Parent
	parts_[(int)Parts::kBody]->SetParent(&worldTransform_);
	//顔<-体
	parts_[(int)Parts::kFace]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//眉毛<-顔
	parts_[(int)Parts::kEyeBrows]->SetParent(&parts_[(int)Parts::kFace]->GetWorldTransform());
	//髪<-顔
	parts_[(int)Parts::kHair]->SetParent(&parts_[(int)Parts::kFace]->GetWorldTransform());
	//左腕<-体
	parts_[(int)Parts::kLeftArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//右腕<-体
	parts_[(int)Parts::kRightArm]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//左腿<-体
	parts_[(int)Parts::kLeftThigh]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	//左脛<-左腿
	parts_[(int)Parts::kLeftLeg]->SetParent(&parts_[(int)Parts::kLeftThigh]->GetWorldTransform());
	// 右腿<-体
	parts_[(int)Parts::kRightThigh]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 右脛<-右腿
	parts_[(int)Parts::kRightLeg]->SetParent(&parts_[(int)Parts::kRightThigh]->GetWorldTransform());
	// 服上<-体
	parts_[(int)Parts::kUpperClothing]->SetParent(&parts_[(int)Parts::kBody]->GetWorldTransform());
	// 服下<-服上
	parts_[(int)Parts::kLowerClothing]->SetParent(&parts_[(int)Parts::kUpperClothing]->GetWorldTransform());
	// 武器<-左腕
	parts_[(int)Parts::kStaff]->SetParent(&parts_[(int)Parts::kLeftArm]->GetWorldTransform());
}

// 振る舞いのセッター
void PlayerModel::SetBehaviorRequest(const IPlayerModel::Behavior& behavior) {
	for (int i = 0; i < parts_.size(); i++) {
		parts_[i]->SetBehaviorRequest(behavior);
	}
}

// ふるまいのゲッター
IPlayerModel::Behavior PlayerModel::GetBehavior() { return parts_[(int)Parts::kBody]->GetBehavior(); }

// モーションの継続時間のリセット
void PlayerModel::SetActionTime(float actionTime) {
	for (int i = 0; i < parts_.size(); i++) {
		parts_[i]->SetActionTimer(actionTime);
	}
}

// アクションタイマーのゲッター
float PlayerModel::GetActionTimer() { return parts_[(int)Parts::kBody]->GetActionTimer(); }

#pragma endregion
