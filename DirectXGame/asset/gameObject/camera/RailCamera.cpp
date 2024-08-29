#include "RailCamera.h"
#include "asset/math/Math.h"
#include "imgui.h"

// 初期化
void RailCamera::Initialize(const Matrix4x4& matWorld, const Vector3& radian) {
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.matWorld_ = matWorld;                       // ワールド座標を設定
	worldTransform_.rotation_ = radian;                         // 回転角を設定
	worldTransform_.translation_ = Vector3({0.0f, 0.0f, 0.0f}); // カメラの初期位置を設定
	// ビュープロジェクションの初期化
	viewProjection_.farZ = 2000;
	viewProjection_.Initialize();
}

// 更新
void RailCamera::Update() {
	// 移動
	worldTransform_.translation_ += Vector3({0.0f, 0.0f, -0.0f});
	// ワールド行列を再計算
	worldTransform_.UpdateMatrix();
	// カメラのオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = ~worldTransform_.matWorld_;

	// カメラの座標を画面に表示する処理
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
}

// ビュープロジェクションのゲッター
const ViewProjection& RailCamera::GetViewProjection() const {
	// TODO: return ステートメントをここに挿入します
	return viewProjection_;
}

// ワールドトランスフォームのゲッター
const WorldTransform& RailCamera::GetWorldTransform() const {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// トランスレイションのセッター
void RailCamera::SetTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }

// ローテションのセッター
void RailCamera::SetRotation(Vector3 rotation) { worldTransform_.rotation_ = rotation; }
