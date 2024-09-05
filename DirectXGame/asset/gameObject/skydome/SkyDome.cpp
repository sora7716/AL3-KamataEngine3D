#include "SkyDome.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"
using namespace std::numbers;

#ifdef _DEBUG
#include <imgui.h>
using namespace ImGui;
#endif // _DEBUG


void SkyDome::Initialize(Model *model,ViewProjection *viewProjection) {

	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize(); 
	worldTransform_.rotation_.x = pi_v<float> / 2.f;

}

void SkyDome::Update() {

	Begin("skyDome");
	DragFloat3("skydome.translate", &worldTransform_.translation_.x, 0.01f);
	End();

	worldTransform_.rotation_.z += 0.005f;
	worldTransform_.UpdateMatrix();
}

void SkyDome::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_); 
}
