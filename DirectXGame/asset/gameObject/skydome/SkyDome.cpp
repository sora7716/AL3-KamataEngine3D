#include "SkyDome.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"
#include <numbers>
using namespace std::numbers;
#include "TextureManager.h"

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
	texture_ = TextureManager::Load("SkyEntyu_ground.png");
}

// 更新
void SkyDome::Update(bool isMove, bool isTitle) {
	// スカイドームを移動
	if (isMove) {
		if (velocityZ_ >= kLimitVelocity) {
			velocityZ_ = kLimitVelocity;
		} else {
			// 速度を加算
			VelocityAdd();
		}
		worldTransform_.translation_.z -= velocityZ_; // 移動
		worldTransform_.rotation_.z += 0.005f;       // 回転
	}
	if (isTitle) {
		worldTransform_.rotation_.y += 0.005f; // 回転
	}
#ifdef _DEBUG
	Begin("skyDome");
	DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	DragFloat("velocityZ", &velocityZ_, 0.1f);
	ImGui::Text("addTime:%d", velocityZAddTime_);
	End();
#endif // _DEBUG
	worldTransform_.UpdateMatrix();//行列の更新
}

// 描画
void SkyDome::Draw(bool isSky) {
	if (isSky) {
		model_->Draw(worldTransform_, *viewProjection_);//空
	} else {
		model_->Draw(worldTransform_, *viewProjection_,texture_);//地下
	}
}

// ワールド座標のゲッター
Vector3 SkyDome::GetWorldPosition() const {
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

// 速度Zのゲッター
float SkyDome::GetVelocityZ() const { return velocityZ_; }

// ローカル座標のゲッター
Vector3 SkyDome::GetTranslation() { return worldTransform_.translation_; }

// ワールドトランスフォームのゲッター
WorldTransform& SkyDome::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

// 速度を加算する
void SkyDome::VelocityAdd() {
	// 時間を計測
	if (velocityZAddTime_-- < 0) {
		velocityZ_++;                         // 速度を加算
		velocityZAddTime_ = kAddTimeInterval; // 時間をリセット
	}
}
