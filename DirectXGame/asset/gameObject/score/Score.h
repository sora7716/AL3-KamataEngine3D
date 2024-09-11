#pragma once
#include "Vector2.h"
#include "WorldTransform.h"
class Sprite;

class Score {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Score() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Score() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Update(int width);

	void TextUpdate();

	/// <summary>
	/// 描画
	/// </summary>
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

	/// <summary>
	/// 計算
	/// </summary>
	void CalculateDigits(); 

	/// <summary>
	/// スコアの登場
	/// </summary>
	void EaseMove();

private:

	uint32_t numberTexture[10];
	uint32_t textTexture[2];
	int digits[7];              

	WorldTransform worldTransform_; 
	Sprite* scoreSprites[7];
	Sprite* textSprites[2];


	int scoreUpTimer_ = 0;
	Vector2 scale_ = {71, 112};
};
