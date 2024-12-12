#include "BasePlayer.h"

// 初期化
void BasePlayer::Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) {
	// 初期化
	BaseCharacter::Initialize(std::move(models), viewProjection);
}

// 更新
void BasePlayer::Update() {
	// 更新
	BaseCharacter::Update();
}

// 描画
void BasePlayer::Draw() {
	// 描画
	BaseCharacter::Draw();
}
