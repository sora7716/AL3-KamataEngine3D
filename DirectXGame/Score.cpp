#include "Score.h"
#include "Sprite.h"

Score::~Score() {
	delete sprite_;
}

void Score::Initialize(uint32_t numberTexture[10]) {

	for (uint32_t i = 0; i < 10; i++) {

		sprite_ = Sprite::Create(numberTexture[i], {10.f + i * 64, 10});
	}

}

void Score::Update() {

	saveNum = number; // 保存用変数にnumberを代入する

	eachNumber[0] = number / 10000; // 万の位をnumber / 10000で切り捨てる
	number = number % 10000;        // numberに10000で割った余りを代入する

	eachNumber[1] = number / 1000; // 千の位をnumber / 1000で切り捨てる
	number = number % 1000;        // numberに1000で割った余りを代入する

	eachNumber[2] = number / 100; // 百の位をnumber / 100で切り捨てる
	number = number % 100;        // numberに100で割った余りを代入する

	eachNumber[3] = number / 10; // 十の位にnumber / 10で切り捨てる
	number = number % 10;        // numberに10で割った余りを代入する

	eachNumber[4] = number / 1; // 一の位をnumber / 1で切り捨てる
	number = number % 1;        // numberに1で割った余りを代入する

	number = saveNum; // numberに保存用変数を代入する

}

void Score::Draw(uint32_t numberTexture[10]) {

	for (uint32_t i = 0; i < numberTexture[eachNumber[COUNT_MAX]]; i++) {
		sprite_->Draw();
	}

}