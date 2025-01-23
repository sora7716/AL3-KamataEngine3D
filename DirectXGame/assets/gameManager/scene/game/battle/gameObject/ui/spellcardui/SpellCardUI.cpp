#include "assets/gameManager/scene/game/battle/gameObject/ui/spellcardui/SpellCardUI.h"
#include "Model.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"

#include "cassert"

void SpellCardUI::Initialize(Model* model, ViewProjection* viewProjection) {
	// NULLチェック
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();

	Vector3 pos{1.67,-0.77,3.13};
	Vector3 rotation{9.120,12.25,9.48};
	Vector3 scale{0.20,0.20,0.5};

	worldTransform_.translation_ = pos;
	worldTransform_.rotation_ = rotation;
	worldTransform_.scale_ = scale;

}

void SpellCardUI::Update() {
	worldTransform_.UpdateMatrix();

#ifdef _DEBUG
	ImGui::Begin("SpellCardUI");
	ImGui::DragFloat3(".translate", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3(".rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif // _DEBUG
}

void SpellCardUI::Draw(uint32_t textureHandle) { model_->Draw(worldTransform_, *viewProjection_, textureHandle); }