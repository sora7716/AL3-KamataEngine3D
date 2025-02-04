#include "BaseCharacter.h"

//初期化
void BaseCharacter::Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models) {
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	//モデルを受け取る
	for (auto model:models) {
		assert(model);
		models_.push_back(model);
	}
}

//更新
void BaseCharacter::Update() { 
	worldTransform_.UpdateMatrix(); 
}

//描画
void BaseCharacter::Draw() {

}

//ワールドトランスフォームのゲッター
const WorldTransform* BaseCharacter::GetWorldTransform() { return &worldTransform_; }