#include "SceneText.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"
#include "asset/math/easing/Easing.h"
#include "asset/math/Math.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


void SceneText::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_.x = -20.26f;
	worldTransform_.translation_.y = -3.f;
	worldTransform_.translation_.z = -36.f;
}

void SceneText::Update() {

	ImGui::Begin("sceneText");
	ImGui::DragFloat3("translate", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
}

void SceneText::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}

void SceneText::SetPosition(const Vector3& position) {

	worldTransform_.translation_ = position;

}

void SceneText::ResultEaseInMove(){

	float endFrame = 122;

	if (resultFrame[0] != endFrame) {
		++resultFrame[0];
	}

	float easing = Easing::OutBounce(resultFrame[0] / endFrame);

	static float begin = worldTransform_.translation_.x;
	static float end = -0.36f;

	worldTransform_.translation_.x = Math::Lerp(begin, end, easing);

}

void SceneText::ResultEaseOutMove() {

	float endFrame = 100;

	if (resultFrame[1] != endFrame) {
		resultFrame[1]++;
	}

	float easing = Easing::InBack(resultFrame[1] / endFrame);

	static float begin = worldTransform_.translation_.x;
	static float end = 15;

	worldTransform_.translation_.x = Math::Lerp(begin, end, easing);

}