#pragma once
#include "Sprite.h"
#include <memory>
#include "assets/math/Math.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

//前方宣言
class Model;
class Player;

class SpellCardUI {
public:
	SpellCardUI() = default;
	~SpellCardUI() = default;

	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw(uint32_t textureHandle);

	void SetParent(const WorldTransform*parent) { worldTransform_.parent_ = parent; }
private:
	enum class SpellCardLabel {
		kFire,
		kThunder,
		kWater,
		kNumOfLabels
	};
	std::vector<std::unique_ptr<Sprite>> sprites_;
	std::vector<uint32_t> textureHandle_;

	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;

	Vector3 targetOffset_ = { 0, 2, 3.0f };

	// 追従対象
	const WorldTransform* target_ = nullptr;
	// 追従対象(プレイヤー)
	Player* targetPlayer_ = nullptr;
};