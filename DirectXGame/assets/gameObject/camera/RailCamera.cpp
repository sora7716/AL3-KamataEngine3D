#include "RailCamera.h"
#include "PrimitiveDrawer.h"
#include "assets/math/Math.h"
#include "Input.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void RailCamera::Initialize(ViewProjection* viewProjection) {

	viewProjection_ = viewProjection;

	input_ = Input::GetInstance();
}

// 更新
void RailCamera::Update() {
	
	if (target_) {

		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		Matrix4x4 rotateYMatrix = Math::MakeRotateYMatrix(viewProjection_->rotation_.y);

		offset = Math::TransformNormal(offset, rotateYMatrix);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_->translation_ = target_->translation_ + offset;
	}

	RailCamera::JoyStickRotation();

	viewProjection_->UpdateMatrix();
	
}

void RailCamera::JoyStickRotation() {

	XINPUT_STATE joyState;

	if (input_->GetJoystickState(0, joyState)) {

		const float kRotateSpeed = 1.f / 60.f;

		viewProjection_->rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kRotateSpeed;
	}

}

// ビュープロジェクションのゲッター
const ViewProjection* RailCamera::GetViewProjection(){
	// TODO: return ステートメントをここに挿入します
	return viewProjection_;
}

