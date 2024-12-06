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
		if (behavior_ != PlayerMode::kRoot) {
			behaviorRequest_ = PlayerMode::kRoot;
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
PlayerMode IPlayerModel::GetBehavior() { return behavior_; }

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
void IPlayerModel::BehaviorDashReset() {
}

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

#pragma region 頭
// 初期化
void Head::Initialize(Model* model, ViewProjection* viewProjection) {
	IModel::Initialize(model, viewProjection);
	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
}

// 更新
void Head::Update() {
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
void Head::BehaviorBlowUpdate() {}

// ダッシュ
void Head::BehaviorDashUpdate() {}

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
void Body::BehaviorRootUpdate() {
	worldTransform_.rotation_ = {};
	worldTransform_.translation_.y = UpdateFloatingGimmick();
}

// 打撃
void Body::BehaviorBlowUpdate() {
	worldTransform_.rotation_ = {};
	worldTransform_.translation_.y = UpdateFloatingGimmick();
}

// ダッシュ
void Body::BehaviorDashUpdate() {
	worldTransform_.rotation_.x = 0.4f;
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
	// 振る舞いの更新
	IPlayerModel::Update();
	// モデルの更新
	IModel::Update();
}

// デバックテキスト
void RightArm::DebugText() {
	IModel::DebugText("rightArm");
}

// 描画
void RightArm::Draw() { IModel::Draw(); }

// 通常行動用
void RightArm::BehaviorRootUpdate() {
	// アニメーションの更新
	worldTransform_.rotation_.x = UpdateTriangleGimmick();
}

// 打撃用
void RightArm::BehaviorBlowUpdate() {
	IPlayerModel::BlowChangeTimer();
	worldTransform_.rotation_.x = AngleLerpAnimation(easingMode_);
}

// 打撃用の初期化
void RightArm::BehaviorBlowReset() {
	IPlayerModel::BehaviorBlowReset();
	angleTimer_ = 0.0f;
}

// ダッシュ
void RightArm::BehaviorDashUpdate() {
	motionTime_ = 1.0f;
	startAngle_ = 90.0f;
	endAngle_ = 45.0f;
	worldTransform_.rotation_.x = TriangleLerpAnimation(EasingMode::kNormal);
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
	IPlayerModel::BlowChangeTimer();
	worldTransform_.rotation_.x = AngleLerpAnimation(easingMode_);
}

// 打撃用の初期化
void LeftArm::BehaviorBlowReset() {
	IPlayerModel::BehaviorBlowReset();
	angleTimer_ = 0.0f;
}

// ダッシュ
void LeftArm::BehaviorDashUpdate() {
	motionTime_ = 1.0f;
	startAngle_ = 90.0f;
	endAngle_ = 45.0f;
	worldTransform_.rotation_.x = TriangleLerpAnimation(EasingMode::kNormal);
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

AABB PlayerModel::GetAABB(Parts partsName){
	return parts_[(int)partsName]->GetAABB();
}

#pragma endregion
