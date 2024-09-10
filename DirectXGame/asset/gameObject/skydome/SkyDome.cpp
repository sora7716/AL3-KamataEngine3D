#include "SkyDome.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"
using namespace std::numbers;

#ifdef _DEBUG
#include <imgui.h>
using namespace ImGui;
#endif // _DEBUG

// 初期化
void SkyDome::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_.z = 1252; // スカイドームの一番端から
	worldTransform_.rotation_.x = pi_v<float> / 2.f;
}

// 更新
void SkyDome::Update(bool isMove, bool isTitle) {

	#ifdef _DEBUG
	ImGui::Begin("skyDome");
	DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	DragFloat("velocityZ", &velocityZ, 0.1f);
	ImGui::Text("addTime:%d", velocityZAddTime);
	ImGui::End();
#endif // _DEBUG

	// スカイドームを移動
	if (isMove) {
		if (velocityZ>=15.0f) {
			velocityZ = 15.0f;
		} else {
			// 速度を加算
			VelocityAdd();
		}
		worldTransform_.translation_.z -= velocityZ; // 移動
		worldTransform_.rotation_.z += 0.005f;       // 回転
	}
	if (isTitle) {
		worldTransform_.rotation_.y += 0.005f; // 回転
	}
	worldTransform_.UpdateMatrix();
}

// 描画
void SkyDome::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

// ワールド座標のゲッター
Vector3 SkyDome::GetWorldTransform() const {
	Vector3 worldPos = {
	    worldTransform_.matWorld_.m[3][0],
	    worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2],
	};
	return worldPos;
}

// トランスレイションのセッター
void SkyDome::SetTranslation(const Vector3& position) { worldTransform_.translation_ = position; }

// ローテーションのセッター
void SkyDome::SetRotation(const Vector3& rotation) { worldTransform_.rotation_ = rotation; }

//速度Zのゲッター
float SkyDome::GetVelocityZ() const { return velocityZ; }

// 速度を加算する
void SkyDome::VelocityAdd() {
	// 時間を計測
	if (velocityZAddTime-- < 0) {
		velocityZ++;//速度を加算
		velocityZAddTime = kAddTimeInterval;//時間をリセット
	}
}