#pragma once
#include "Vector2.h"
#include "WorldTransform.h"
class Sprite;

class Score {

public:

	~Score();

	void Initialize();

	void Update(int width);

	void TextUpdate();

	void Draw();

	//スコア用のテキスト描画
	void TextDraw();

	//ハイスコア用のテキスト描画
	void HighTextDraw();

	/// <summary>
	/// スコアのセッター
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(int score);

	void SetScale(Vector2 scale);
	void SetPosition(const Vector3& position);
	void SetTextPosition(const Vector3& position);


private:

	void CalculateDigits(); 

	void EaseMove();

private:

	uint32_t numberTexture[10];
	uint32_t textTexture[2];
	int digits[7];              

	WorldTransform worldTransform_; 
	Sprite* scoreSprites[7];
	Sprite* textSprites[2];

	int score_ = 0000000;

	int scoreUpTimer_ = 0;
	Vector2 scale_ = {71, 112};
};
