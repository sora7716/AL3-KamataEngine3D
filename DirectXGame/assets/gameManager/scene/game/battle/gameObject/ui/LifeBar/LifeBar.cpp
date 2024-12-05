#include "LifeBar.h"
#include "ImGuiManager.h"
#include "assets/math/easing/Easing.h"
#include "WorldTransform.h"
#include "WinApp.h" //画面のサイズを使用するため
#include "input/Input.h"

void LifeBar::Initialize(const std::vector<uint32_t>&& textures){
	sprites_.resize((int)Label::kNumOfLabels); 
	for (int i = 0; i < (int)Label::kNumOfLabels; i++) {
		sprites_[i].reset(Sprite::Create(textures[i], {(WinApp::kWindowWidth / 2) - (width_ / 2), WinApp::kWindowHeight / 2}));
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
