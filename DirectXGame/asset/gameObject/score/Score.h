#pragma once

#include "WorldTransform.h"
class Sprite;

class Score {

public:

	~Score();

	void Initialize();

	void Update();

	void Draw();

private:

	uint32_t numberTexture[10]; 
	int digits[7];              

	void CalculateDigits(int score); 

	WorldTransform worldTransform_; 
	Sprite* sprites[7];       

	int score_ = 0;

};
