#include "RailCamera.h"
#include "PrimitiveDrawer.h"
#include "assets/math/Math.h"
#include "input.h"
#include "assets/gameObject/player/Player.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void RailCamera::Initialize(ViewProjection* viewProjection) {
	
	viewProjection_ = viewProjection;

	input_ = Input::GetInstance();

	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(viewProjection);
}

// 更新
void RailCamera::Update() {
	// カメラ補間変数
	static float cameraLerp = 0.2f;

	if (target_) {
		// 追従座標の補間
		interTarget_ = Math::Lerp(interTarget_, target_->translation_, cameraLerp);
	}

	// 追従対象からのオフセット
	Vector3 offset = CalcOffset();
	// カメラ座標
	viewProjection_->translation_ = interTarget_ + offset;
	// ジョイスティックによるカメラの回転
	RailCamera::JoyStickRotation();
	// ビュー行列の更新
	viewProjection_->UpdateViewMatrix();
}

void RailCamera::Reset() {

	// 追従対象がいれば
	if (target_) {
		// 追従座標・角度の初期化
		interTarget_ = target_->translation_;
		viewProjection_->rotation_.y = target_->rotation_.y;
	}

	desticationAngleY = viewProjection_->rotation_.y;

	// 追従対象からのオフセット
	Vector3 offset = CalcOffset();
	// カメラ座標
	viewProjection_->translation_ = interTarget_ + offset;
}

void RailCamera::SetTarget(const WorldTransform* target) {
	target_ = target;
	RailCamera::Reset();
}

void RailCamera::JoyStickRotation() {

	XINPUT_STATE joyState;

	if (!input_->GetJoystickState(0, joyState)) {
		return;
	}

	const float kRotateSpeed = 1.f / 60.f;

	viewProjection_->rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * kRotateSpeed;

	if ((joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
		float targetAngle = target_->rotation_.y + 2 * float(3.14);

		const float rotateLerpSpeed = 0.03f;
		viewProjection_->rotation_.y = Lerp(viewProjection_->rotation_.y, targetAngle, rotateLerpSpeed);
	}
};

Vector3 RailCamera::CalcOffset() const {

	Vector3 offset = {0.0f, 2.0f, -10.0f};

	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);

	offset = TransformNormal(offset, rotateYMatrix);

	return offset;
}

