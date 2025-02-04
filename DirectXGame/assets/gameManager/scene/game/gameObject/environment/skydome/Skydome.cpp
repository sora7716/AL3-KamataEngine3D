#include "Skydome.h"

// 初期化
void Skydome::Initialize(ViewProjection* viewProjection, std::shared_ptr<Model>&& model) { BaseEnvironment::Initialize(viewProjection, std::move(model)); }

// 更新
void Skydome::Update() { BaseEnvironment::Update(); }

// 描画
void Skydome::Draw() { BaseEnvironment::Draw(); }
