#include "LifeBar.h"
#include "ImGuiManager.h"
#include "assets/math/easing/Easing.h"
#include "WorldTransform.h"
#include "WinApp.h" //画面のサイズを使用するため
#include "input/Input.h"
#include "assets/gameManager/scene/game/baseGameObject/baseCharacter/BaseCharacter.h"

LifeBar::LifeBar(int characterType) {
	characterType_ = characterType;

	currentHP_ = 0;
	targetHP_ = 0;
	maxHP_ = 0;
	dmgTimer_ = 0;
	characterType_ = 0;

	if (characterType == static_cast<int>(BaseCharacter::CharType::kPlayer)) {
		pos_ = { WinApp::kWindowWidth / 2 - (width_ + 70), 650 }; //650は画面のちょうどいいところだと思って付けました。
	}
	if (characterType == static_cast<int>(BaseCharacter::CharType::kEnemy)) {
		pos_ = { WinApp::kWindowWidth / 2 - width_ / 2, 50 }; //敵の上に付けたいけど、今は適当
	}
}



void LifeBar::Initialize(const std::vector<uint32_t>&& textures){
	sprites_.resize((int)Label::kNumOfLabels);
	for (int i = 0; i < (int)Label::kNumOfLabels; i++) {
		sprites_[i].reset(Sprite::Create(textures[i], pos_));
	}
	if (characterType_ == static_cast<int>(BaseCharacter::CharType::kEnemy)) {
		sprites_[1].reset(Sprite::Create(textures[3], pos_));//ライフバー色を変える
	}
	maxHP_ = sprites_[(int)Label::kHealth]->GetSize().x;
	currentHP_ = maxHP_;
}

bool LifeBar::Update() {
	AdjustHP();
	CoolDown();

	bool checkIfDead = GetIsDead();
	return checkIfDead;
}

void LifeBar::Draw() {
	for (const auto& sprit : sprites_) {
		sprit->Draw();
	}
}

void LifeBar::AdjustHP() {
	dmgTimer_ += kDuration_;
	//ライフバーを徐々に減る処理
	if (sprites_[(int)Label::kDamage]->GetSize().x > sprites_[(int)Label::kHealth]->GetSize().x) {
		currentHP_ = (float)std::lerp(currentHP_, targetHP_, Easing::GetInstance()->InSine(dmgTimer_));//

		//Vector2型に変更
		Vector2 adjustedHealth{
			currentHP_,
			sprites_[(int)Label::kHealth]->GetSize().y //変更なし
		};
		//体力更新
		sprites_[(int)Label::kDamage]->SetSize(adjustedHealth);
	}
}

void LifeBar::TookDamage() {
	if (sprites_[(int)Label::kHealth]->GetSize().x > 14 && !isDamaged_) { //14はピックセルサイズ、ライフバーの幅と比べてる
		//受けたダメージの計算
		Vector2 targetHP{
			(float)sprites_[(int)Label::kHealth]->GetSize().x - 50,
			(float)sprites_[(int)Label::kHealth]->GetSize().y //変化なし
		};

		//14は画像のサイズなので、14だともう死んでいる。
		//死亡確認
		if (targetHP.x <= 14) {
			targetHP.x = 14;
			sprites_[(int)Label::kHealth]->SetColor({});
			sprites_[(int)Label::kDamage]->SetColor({});
			isDead_ = true;
		}

		//体力を更新
		sprites_[(int)Label::kHealth]->SetSize(targetHP);
		//AdjustHP()準備
		targetHP_ = targetHP.x;
		//タイマー開始準備
		coolDownTimer_ = 120;
		dmgTimer_ = 0;
		//ダメージを受けたフラグ
		isDamaged_ = true;
	}
}

void LifeBar::CoolDown() {
	coolDownTimer_--;
	if (coolDownTimer_ < coolDownDuration) {
		//coolDownTimerによってダメージを受けないようにする
		isDamaged_ = false;
	}
}

void LifeBar::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("enemy");
	ImGui::Text("frame.%f", dmgTimer_);
	ImGui::Text("second.%f", kDuration_);
	ImGui::Text("coolDownTimer_.%f", coolDownTimer_);
	ImGui::End();
#endif // _DEBUG
}