#include "SpellCard.h"
#include "cassert"
#include "Model.h"
#include "ViewProjection.h"

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化処理
void SpellCard::Initialize(Model* model, ViewProjection* viewProjection) {
	// NULLチェック
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();


}

// 更新処理
void SpellCard::Update() {

#ifdef _DEBUG

	DebugText("SpellCard");

#endif // _DEBUG

	worldTransform_.UpdateMatrix();
}

// 描画処理
void SpellCard::Draw(uint32_t textureHandle) {
	model_->Draw(worldTransform_,*viewProjection_,textureHandle); 
}

// デバッグテキスト
void SpellCard::DebugText(const char* label) {
	(void)label;
#ifdef _DEBUG
	ImGui::Begin(label);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
}