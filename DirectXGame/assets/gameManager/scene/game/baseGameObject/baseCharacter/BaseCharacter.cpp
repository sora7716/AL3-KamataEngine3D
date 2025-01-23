#include "BaseCharacter.h"
#include "ImGuiManager.h"
#include <cassert>
// 初期化

void BaseCharacter::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection, const std::vector<uint32_t>&& textures){
	// モデルを入れていく
	for (int i = 0; i < models.size(); i++) {
		assert(models[i]);
		models_.push_back(models[i].get());
	}

	for (int i = 0; i < textures.size(); i++) {
		textures_.push_back(textures[i]);
	}
	viewProjection_ = viewProjection;
	wireFrame_ = new OBB();
	wireFrame_->Initialize({ .size = worldTransform_.scale_, .rotation = worldTransform_.rotation_, .center = GetWorldPos() }, viewProjection);
	worldTransform_.Initialize();

	kWidth_ = 3.0f;
	kHeight_ = 3.0f;
	kDepth_ = 3.0f;
}

// 更新
void BaseCharacter::Update() {
	worldTransform_.UpdateMatrix();
	wireFrame_->Update();
}

// 描画
void BaseCharacter::Draw() {}

// ワイヤーフレームの表示
void BaseCharacter::DrawWire() {
	wireFrame_->Draw(); 
}

// デバックテキスト
void BaseCharacter::DebugText(const char* label) {
	(void)label;
#ifdef _DEBUG
	ImGui::Begin(label);
	ImGui::DragFloat3("scale", &worldTransform_.translation_.x, 0.1f, 0.0f, 3.0f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG
}

// ワールドトランスフォームのゲッター
const WorldTransform& BaseCharacter::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

const Vector3 BaseCharacter::GetWorldPos() { return {worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]}; }

// ビュープロジェクションのゲッター
ViewProjection& BaseCharacter::GetViewProjection() {
	// TODO: return ステートメントをここに挿入します
	return *viewProjection_;
}
