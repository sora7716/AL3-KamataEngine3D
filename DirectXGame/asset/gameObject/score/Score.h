#pragma once

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

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// スコアのセッター
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(int score);

	/// <summary>
	/// スコアのゲッター
	/// </summary>
	/// <returns></returns>
	int GetScore();

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

	uint32_t numberTexture[10]; //テクスチャの数
	int digits[7];//数字の桁数


	WorldTransform worldTransform_; //ワールドトランスフォーム
	Sprite* sprites[7];//スプライトの数

	int score_ = 0000000;//スコア
};
