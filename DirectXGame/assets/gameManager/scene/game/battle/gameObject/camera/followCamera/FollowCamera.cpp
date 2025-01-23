#include "FollowCamera.h"
#include "assets/math/Math.h"
#include "input/Input.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"
#include "assets/math/Math.h"
// 初期化
void FollowCamera::Initialize() { 
	viewProjection_.Initialize(); 

	viewProjection_.rotation_.x = 0.31f;

	worldTransform_.Initialize();
}

// 更新
void FollowCamera::Update() {

	if (Input::GetInstance()->TriggerKey(DIK_T)) {
		isCameraExChange_ ^= true;
	}
#ifdef _DEBUG
	ImGui::Begin("camera");
	ImGui::DragFloat3(".offset", &targetOffset_.x, 0.01f);
	ImGui::DragFloat3(".rotation", &viewProjection_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG

	(this->*cameraUpdateTable[static_cast<size_t>(cameraPhase_)])();

	viewProjection_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
	viewProjection_.matView = ~worldTransform_.matWorld_;
}

// ビュープロジェクションのゲッター
ViewProjection& FollowCamera::GetViewProjection() { return viewProjection_; }

WorldTransform& FollowCamera::GetWorldTransform(){
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// ゲームパッドの操作
void FollowCamera::GamepadControl() {
	// ゲームパッド
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 回転速度
		const float rot = -5.0f * deltaTime;
		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * rot;
	}
}

// キーボードの操作
void FollowCamera::KeyboardControl() {
	const float rot = 5 * deltaTime;
	float move = 0.0f;
	if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		move = -1.0f;
	} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
		move = 1.0f;
	}
	move = Math::Normalize(move) * rot;
	viewProjection_.rotation_.y += move;
}

// 追従カメラの更新処理
void FollowCamera::FollowCameraUpdate() {

	if (!isCameraExChange_) {
		cameraPhase_ = CameraPhase::kCameraController;
	
	} else {

		if (target_) {
			// 追従対象からカメラまでのオフセット
			Vector3 offset = {0.0f, 2.0f, -10.0f};
			Matrix4x4 rotateMat = Math::MakeRotateXYZMatrix(viewProjection_.rotation_);
			
			offset = Math::TransformNormal(offset, rotateMat);
			// 座標をコピーしてオフセット分ずらす
			viewProjection_.translation_ = target_->translation_ + offset;
			
		}
	}
}

// カメラ制御の更新処理
void FollowCamera::CameraControllerUpdate() {

	if (isCameraExChange_) {
		cameraPhase_ = CameraPhase::kFollow;
	} else {

		// 追従対象のワールドトランスフォームを参照
		const WorldTransform& targetWorldTransform = targetPlayer_->GetWorldTransform();
		// 追従対象とオフセットからカメラの目標座標を計算
		targetPos_ = targetWorldTransform.translation_ + targetOffset_;
		// 座標補間によりゆったり追従
		worldTransform_.translation_ = Math::Lerp(worldTransform_.translation_, targetPos_, kInterpokationRate_);
		float viewProjectionX = worldTransform_.translation_.x;
		float viewProjectionY = worldTransform_.translation_.y;
		// カメラの移動範囲を制限する
		worldTransform_.translation_.x = std::clamp(viewProjectionX, movableArea_.left, movableArea_.right);
		worldTransform_.translation_.y = std::clamp(viewProjectionY, movableArea_.bottom, movableArea_.top);
	}
}

// リセット
void FollowCamera::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = targetPlayer_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

// カメラ更新処理テーブル
void (FollowCamera::*FollowCamera::cameraUpdateTable[])(){
	&CameraControllerUpdate, // カメラコントローラの更新処理
	&FollowCameraUpdate,     // 追従カメラの更新処理
};