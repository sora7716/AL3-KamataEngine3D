#define NOMINMAX
#include "CameraController.h"
#include "gameObject/player/Player.h"
#include <algorithm>
#include "ImGuiManager.h"

//初期化
void CameraController::Initialize() { 
	viewProjection_.Initialize(); //viewProjection_の初期化　
	targetOffset_.SetVector({0, 0, -34.0f});//ターゲットからの距離
}

//更新処理
void CameraController::Update() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	goalPosition_ = targetWorldTransform.translation_ + targetOffset_ + target_->GetVelocity() * kVelocityBias;//ターゲットの速度から目標ポジションを算出
	viewProjection_.translation_  = Lerp(viewProjection_.translation_,goalPosition_,kInterpolationRate);//線形補完で少し遅らせる
	//プレイヤーにどこまで追従するか↓
	viewProjection_.translation_.x = std::clamp(
		viewProjection_.translation_.x, 
		movableArea_.left, 
		movableArea_.right
	);//x座標の追従する範囲

	viewProjection_.translation_.y = std::clamp(
		viewProjection_.translation_.y, 
		movableArea_.bottom, 
		movableArea_.top
	); // y座標の追従する範囲
	// プレイヤーにどこまで追従するか↑

	//プレイヤーが見切れないようにするためのもの↓
	viewProjection_.translation_.x = std::clamp(
	    viewProjection_.translation_.x,
	    target_->GetWorldTransform().translation_.vector.x + margin.left,
	    target_->GetWorldTransform().translation_.vector.x + margin.right);

	viewProjection_.translation_.y = std::clamp(
	    viewProjection_.translation_.y,
	    target_->GetWorldTransform().translation_.vector.y + margin.bottom,
	    target_->GetWorldTransform().translation_.vector.y + margin.top);
	// プレイヤーが見切れないようにするためのもの↑

	viewProjection_.UpdateMatrix();//マトリックスの更新

	ImGui::Begin("debug");
	ImGui::DragFloat("targetOffset.x",&targetOffset_.vector.x);
	ImGui::DragFloat("targetOffset.y",&targetOffset_.vector.y);
	ImGui::DragFloat("targetOffset.z",&targetOffset_.vector.z);
	ImGui::End();
}

//リセット
void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;// viewProjection_のtranslation_に代入
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
