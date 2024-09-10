#include "Score.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "asset/math/easing/Easing.h"
#include "asset/math/Math.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

//初期化
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

	///ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//X座標を指定
	worldTransform_.translation_.x = -370.0f;
	
	for (int i = 0; i < 7; ++i) {
		//数字のテクスチャを使用してスプライトを作成し、配列に格納する
		//スプライトの位置は、各数字に対して横方向に50ピクセルずつずらして配置する
		sprites[i] = Sprite::Create(numberTexture[i], {0.5f + (i * 50), 0.5f});
	}

}

//更新
void Score::Update() {

	for (int i = 0; i < 7; ++i) {
		//最初はイージングさせたいため、Initialize関数で指定したX座標に設定する
		sprites[i]->SetPosition({worldTransform_.translation_.x + (i * 50), 0.5f});
	}

	//関数呼び出し
	EaseMove();

	//行列の更新
	worldTransform_.UpdateMatrix();
}

//描画
void Score::Draw() {
	// スコアの桁数を計算する
	CalculateDigits();

	for (int i = 0; i < 7; ++i) {
		// スプライトに対応する桁の数字のテクスチャを設定する
		sprites[i]->SetTextureHandle(numberTexture[digits[i]]);

		// スプライトを描画する
		sprites[i]->Draw();
	}
 
}

//スコアのセッター
void Score::SetScore(int score) { score_ = score; }

//スコアのゲッター
int Score::GetScore() { return score_; }

//桁数を求める
void Score::CalculateDigits() {

	for (int i = 6; i >= 0; --i) {
		// スコアの一桁を取り出し、digits 配列に格納する
		digits[i] = score_ % 10;

		// スコアを10で割って次の桁へ移動する
		score_ /= 10;
	}
}

//スコアの登場
void Score::EaseMove() {

	// フレーム数を管理する変数（静的にして状態を保持）
	static float frame = 0;

	// イージングの終了フレーム数
	static float endFrame = 50;

	if (frame != endFrame) {
		// フレーム数が終了フレームに達していない場合、フレーム数を増やす
		++frame;
	}

	// イージングの値を計算する（フレーム数を正規化して使用）
	float easing = Easing::In(frame / endFrame);

	// イージングの開始位置を設定（初回のみ）
	static float begin = worldTransform_.translation_.x;

	// イージングの終了位置
	static float end = 0.5f;

	// 開始位置と終了位置の間をイージングによって補間する
	worldTransform_.translation_.x = Math::Lerp(begin, end, easing);
}