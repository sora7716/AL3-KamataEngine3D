#include "LifeBar.h"
#include "ImGuiManager.h"
#include "assets/math/easing/Easing.h"
#include "WorldTransform.h"
#include "WinApp.h" //画面のサイズを使用するため
#include "input/Input.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"

LifeBar::LifeBar(int characterType){
	if (characterType == static_cast<int>(BaseCharacter::CharType::kPlayer)) {
		pos_ = { WinApp::kWindowWidth / 2 - (width_ + 70), 650 }; //650は画面のちょうどいいところだと思って付けました。
	}
	if (characterType == static_cast<int>(BaseCharacter::CharType::kEnemy)) {
		pos_ = { WinApp::kWindowWidth / 2 - width_, 200 }; //敵の上に付けたいけど、今は適当
	}
}

void LifeBar::Initialize(const std::vector<uint32_t>&& textures){
	sprites_.resize((int)Label::kNumOfLabels); 
	for (int i = 0; i < (int)Label::kNumOfLabels; i++) {
		sprites_[i].reset(Sprite::Create(textures[i], pos_));
	}

	maxHP_ = sprites_[(int)Label::kHealth]->GetSize().x;
	currentHP_ = maxHP_;
}

void LifeBar::Update(){
	TookDamage();
	AdjustHP();
}

void LifeBar::Draw(){
	for (const auto& sprit : sprites_) {
		sprit->Draw();
	}
}

void LifeBar::AdjustHP(){
	if (!isDamaged_) { return; }
	dmgTimer_ += kDuration_;
	if (sprites_[(int)Label::kDamage]->GetSize().x > sprites_[(int)Label::kHealth]->GetSize().x) {
		currentHP_ = (float)std::lerp(currentHP_, targetHP_, Easing::GetInstance()->InSine(dmgTimer_));

		//Vector2型に変更
		Vector2 adjustedHealth{
			currentHP_,
			sprites_[(int)Label::kHealth]->GetSize().y //変更なし
		};
		//体力更新
		sprites_[(int)Label::kDamage]->SetSize(adjustedHealth);
	}
	if (dmgTimer_ > 1) {
		isDamaged_ = false;
		dmgTimer_ = 0;
	}
	ImGui::Text("frame.%f", dmgTimer_);
	ImGui::Text("second.%f", kDuration_);
}

void LifeBar::TookDamage(){
	//ダメージを喰らう結果確認
	bool space = Input::GetInstance()->TriggerKey(DIK_SPACE);
	
	if (space && sprites_[(int)Label::kHealth]->GetSize().x > 14) {
		//受けたダメージの計算
		Vector2 targetHP{
			(float)sprites_[(int)Label::kHealth]->GetSize().x - 450,
			(float)sprites_[(int)Label::kHealth]->GetSize().y //変化なし
		};

		if (targetHP.x <= 14) {
			targetHP.x = 14;
			sprites_[(int)Label::kHealth]->SetColor({});
			sprites_[(int)Label::kDamage]->SetColor({});
		}

		//体力を更新
		sprites_[(int)Label::kHealth]->SetSize(targetHP);
		//AdjustHP()準備
		targetHP_ = targetHP.x;
		isDamaged_ = true;
	}
}
