#pragma once
#include "WorldTransform.h"
class Sprite;
class Hp {

public:

	void Initialize();

	void Update();

	void Draw();

	int GetHpCount();

	void SetHpCount(int count);

private:

	uint32_t textureHandle_;

	Sprite* sprites_[3];

	WorldTransform worldTransform_;

	//残機
	int hpCount_ = 3;

};
