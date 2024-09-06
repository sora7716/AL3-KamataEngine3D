#include "Score.h"
#include "Sprite.h"
#include "TextureManager.h"

Score::~Score() {}

void Score::Initialize() {

	// スコア
#pragma region 数字の画像を読み込む

	numberTexture[0] = TextureManager::Load("score/0.png");
	numberTexture[1] = TextureManager::Load("score/1.png");
	numberTexture[2] = TextureManager::Load("score/2.png");
	numberTexture[3] = TextureManager::Load("score/3.png");
	numberTexture[4] = TextureManager::Load("score/4.png");
	numberTexture[5] = TextureManager::Load("score/5.png");
	numberTexture[6] = TextureManager::Load("score/6.png");
	numberTexture[7] = TextureManager::Load("score/7.png");
	numberTexture[8] = TextureManager::Load("score/8.png");
	numberTexture[9] = TextureManager::Load("score/9.png");

#pragma endregion

	for (int i = 0; i < 7; ++i) {
		sprites[i] = Sprite::Create(numberTexture[i], {0.5f + i * 40, 0.5f}); // Adjust position as needed
	}

}

void Score::Update() {
}

void Score::Draw() {

	CalculateDigits(score_);

	for (int i = 0; i < 7; ++i) {
		sprites[i]->SetTextureHandle(numberTexture[digits[i]]);
		sprites[i]->Draw();
	}
 
}

void Score::CalculateDigits(int score) {

	for (int i = 6; i >= 0; --i) {
		digits[i] = score % 10;
		score /= 10;
	}
}