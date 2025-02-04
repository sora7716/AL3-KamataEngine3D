#include "Camera.h"
#include "assets/gameManager/math/Math.h"
#include "ImGuiManager.h"

// カメラの初期化
void Camera::Initialize(const Matrix4x4* matWorld,const Vector3* rotate) {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.rotation_ = *rotate;
	worldTransform_.matWorld_ = *matWorld;
	worldTransform_.translation_ = {0.0f, 2.0f, -5.0f};
	// ビュープロジェクションの初期化
	viewProjection_.farZ = 20000;
	viewProjection_.Initialize();
}

// レイルカメラの更新
void Camera::RailUpdate() {
	// ワールド行列を再計算
	worldTransform_.UpdateMatrix();
	// カメラのオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = ~worldTransform_.matWorld_;
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

// フォローカメラの更新
void Camera::FollowUpdate() {
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -5.0f};
		Matrix4x4 rotateMat = Math::MakeRotateXYZMatrix(viewProjection_.rotation_);
		offset = Math::TransformNormal(offset, rotateMat);
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = target_->translation_ + offset;
	}

	viewProjection_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("rotation", &viewProjection_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
}

//フォローカメラの動き
void Camera::FollowMove(float rotSpeed) { 
	viewProjection_.rotation_.y += rotSpeed; 
}

// 追従対処のセッター
void Camera::SetTarget(const WorldTransform* target) { target_ = target; }

// ビュープロジェクションのゲッター
const ViewProjection& Camera::GetViewProjection() const {
	// TODO: return ステートメントをここに挿入します
	return viewProjection_;
}

// ワールドトランスフォームのゲッター
const WorldTransform& Camera::GetWorldTransform() const {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

//更新テーブルの初期化
void (Camera::*Camera::updateTable[])() = {&Camera::RailUpdate, &Camera::FollowUpdate};