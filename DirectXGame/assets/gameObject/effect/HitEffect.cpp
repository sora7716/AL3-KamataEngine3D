#include "HitEffect.h"
#include "cassert"
#include "algorithm"

#ifdef _DEBUG
#include "imgui.h"
using namespace ImGui;
#endif // _DEBUG

void HitEffect::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	
	// ワールド変換データの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0, 0, 0};

	model_->SetAlpha(0.5f);

	interpolationRate = 0.0f;
}

void HitEffect::Update() {

	if (isFinished_) {
		return;
	}

#ifdef _DEBUG
	Begin(std::string("hitEffect").c_str());
	DebugText();
	End();
#endif // _DEBUG


	interpolationRate += 0.05f;
	if (interpolationRate >= 1.0f) {
		interpolationRate = 1.0f;
		isFinished_ = true;
	}

	model_->SetAlpha(Math::Lerp(1.0f,0.0f,interpolationRate));

	Vector3 start = {0.5f, 0.5f, 0.5f};
	Vector3 end = {2.0f, 2.0f, 2.0f};

	worldTransform_.scale_ = Math::Lerp(start, end, interpolationRate);
	worldTransform_.UpdateMatrix();

}

void HitEffect::Draw(const ViewProjection &viewProjection) {

	//終了なら何もしない
	if (isFinished_) {
	   return;
	}

	//モデルの描画
	model_->Draw(worldTransform_, viewProjection);
	
}

void HitEffect::DebugText() {
	std::string debugLabel = "scale";
	DragFloat3(debugLabel.c_str(), &worldTransform_.scale_.x, 0.01f);
	debugLabel = "rotation";
	DragFloat3(debugLabel.c_str(), &worldTransform_.rotation_.x, 0.01f);
	debugLabel = "translation";
	DragFloat3(debugLabel.c_str(), &worldTransform_.translation_.x, 0.01f);
}