#define NOMINMAX
#include "CameraController.h"
#include "gameObject/player/Player.h"
#include <algorithm>

//初期化
void CameraController::Initialize() { 
	viewProjection_.Initialize(); //viewProjection_の初期化　
	targetOffset_.SetVector({0, 0, -50.0f});//ターゲットからの距離
}

//更新処理
void CameraController::Update() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	goalPosition_ = targetWorldTransform.translation_ + targetOffset_;//ターゲットの最終的にいるところを求める
	viewProjection_.translation_  = Lerp(viewProjection_.translation_,goalPosition_,kInterpolationRate);//線形補完で少し遅らせる
	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, movableArea_.left, movableArea_.right);//x座標の追従する範囲
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, movableArea_.bottom,  movableArea_.top);//y座標の追従する範囲
	viewProjection_.UpdateMatrix();//マトリックスの更新
}

//リセット
void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	MyVector3 temp_ = targetWorldTransform.translation_ + targetOffset_;//そのままだとVector3に変換できないから一旦ほかの変数に補完
	viewProjection_.translation_ = (Vector3)temp_.vector;//viewProjection_のtranslation_に代入
}

//ビュープロジェクションのゲッター
ViewProjection& CameraController::GetViewProjection() {
	// TODO: return ステートメントをここに挿入します
	return viewProjection_; 
}

//ターゲットのセッター
void CameraController::SetTarget(Player* target) { target_ = target; }

//movableAreaのセッター
void CameraController::SetMovableArea(Rect area) { movableArea_ = area; }
