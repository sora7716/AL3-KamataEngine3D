#include "SceneText.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


void SceneText::Initialize(Model* model, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(-0.26f, -3, -36);

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