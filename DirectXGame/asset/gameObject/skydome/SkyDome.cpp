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
void SkyDome::Update() {

	Begin("skyDome");
	DragFloat3("translate", &worldTransform_.translation_.x, 0.1f);
	End();
	// スカイドームを移動
	worldTransform_.translation_.z--;
	worldTransform_.rotation_.z += 0.005f; // 回転
	worldTransform_.UpdateMatrix();
}

// 描画
void SkyDome::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

//ワールド座標のゲッター
Vector3 SkyDome::GetWorldTransform() const {
	Vector3 worldPos = {
	    worldTransform_.matWorld_.m[3][0],
	    worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2],
	};
	return worldPos;
}

