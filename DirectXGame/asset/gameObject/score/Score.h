#pragma once

#include "WorldTransform.h"
class Sprite;

class Score {

public:

	~Score();

	void Initialize();

	void Update();

	void Draw();

	/// <summary>
	/// スコアのセッター
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(int score);

private:

	void CalculateDigits(int score); 

	void EaseMove();

private:

	uint32_t numberTexture[10]; 
	int digits[7];              


	WorldTransform worldTransform_; 
	Sprite* sprites[7];       

	int score_ = 0000000;

	int scoreUpTimer_ = 0;
};
