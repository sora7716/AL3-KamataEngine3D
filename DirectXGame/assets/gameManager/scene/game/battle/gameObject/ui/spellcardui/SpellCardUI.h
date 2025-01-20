#pragma once
#include "ViewProjection.h"
#include "Sprite.h"
#include <memory>
#include "assets/math/Math.h"

class SpellCardUI {
public:
	SpellCardUI() = default;
	~SpellCardUI() = default;

	void Initialize();

	void Update();

	void Draw();
private:
	enum class SpellCardLabel {
		kFire,
		kThunder,
		kWater,
		kNumOfLabels
	};
	std::vector<std::unique_ptr<Sprite>> sprites_;
	std::vector<uint32_t> textureHandle_;


};