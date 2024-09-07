#pragma once
#define COUNT_MAX 5

#include "WorldTransform.h"
class Sprite;

class Score {

public:

	~Score();

	void Initialize(uint32_t numberTexture[10]);

	void Update();

	void Draw(uint32_t numberTexture[10]);

private:

	Sprite* sprite_ = nullptr;

	int number = 00000;

	int eachNumber[5];

	int saveNum = 0;

};
