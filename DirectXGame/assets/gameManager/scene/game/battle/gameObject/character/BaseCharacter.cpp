#include "BaseCharacter.h"
#include "ImGuiManager.h"
#include <cassert>
//初期化
void BaseCharacter::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	//モデルを入れていく
	for (int i = 0; i < models.size(); i++) {
		assert(models[i]);
		models_.push_back(models[i].get());
	}
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();

	kWidth_ = 3.0f;
	kHeight_ = 3.0f;
	kDepth_ = 3.0f;
}

//更新
void BaseCharacter::Update() { worldTransform_.UpdateMatrix(); }

//描画
void BaseCharacter::Draw() {}

//デバックテキスト
void BaseCharacter::DebugText(const char* label) { 
	ImGui::Begin(label);
	ImGui::DragFloat3("scale", &worldTransform_.translation_.x, 0.1f, 0.0f, 3.0f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
}

//ワールドトランスフォームのゲッター
const WorldTransform& BaseCharacter::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}

const Vector3 BaseCharacter::GetWorldPos(){
	return {
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2]
	}; 
}

//ビュープロジェクションのゲッター
ViewProjection& BaseCharacter::GetViewProjection() {
	// TODO: return ステートメントをここに挿入します
	return *viewProjection_;
}

AABB BaseCharacter::GetAABB(){
	Vector3 worldpos = GetWorldPos();

	AABB aabb;

	aabb.min = { worldpos.x - kWidth_ / 2.0f, worldpos.y - kHeight_ / 2.0f, worldpos.z - kWidth_ / 2.0f };
	aabb.max = { worldpos.x + kWidth_ / 2.0f, worldpos.y + kHeight_ / 2.0f, worldpos.z + kWidth_ / 2.0f };

	return aabb;
}
