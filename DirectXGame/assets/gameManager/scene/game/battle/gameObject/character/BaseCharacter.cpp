#include "BaseCharacter.h"
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
}

//更新
void BaseCharacter::Update() { worldTransform_.UpdateMatrix(); }

//描画
void BaseCharacter::Draw() {}

//ワールドトランスフォームのゲッター
const WorldTransform& BaseCharacter::GetWorldTransform() {
	// TODO: return ステートメントをここに挿入します
	return worldTransform_;
}
