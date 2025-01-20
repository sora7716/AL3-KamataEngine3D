#include "assets/gameManager/scene/game/battle/gameObject/ui/mpbar/MpBar.h"
#include "ImGuiManager.h"
#include "assets/math/easing/Easing.h"
#include "WorldTransform.h"
#include "WinApp.h" //画面のサイズを使用するため
#include "input/Input.h"
#include "assets/gameManager/scene/game/baseGameObject/baseCharacter/BaseCharacter.h"

MpBar::MpBar(int characterType){
	characterType_ = characterType;

	currentMp_ = 0;
	targetMp_ = 0;
	maxMp_ = 0;
	costTimer_ = 0;
	
	if (characterType == static_cast<int>(BaseCharacter::CharType::kPlayer)) {
		pos_ = { WinApp::kWindowWidth / 2 - (width_ + 70), 650 }; //650は画面のちょうどいいところだと思って付けました。
	}
	if (characterType == static_cast<int>(BaseCharacter::CharType::kEnemy)) {
		pos_ = { WinApp::kWindowWidth / 2 - width_ / 2, 50 }; //敵の上に付けたいけど、今は適当
	}
}

void MpBar::Initialize(const std::vector<uint32_t>&& textures){
	sprites_.resize((int)MpLabel::kNumOfLabels);
	for (int i = 4; i < (int)MpLabel::kNumOfLabels; i++) { //int=4	からはMPの画像です。
		sprites_[i].reset(Sprite::Create(textures[i],pos_));
	}
	maxMp_ = sprites_[(int)MpLabel::kMp]->GetSize().x;
	currentMp_ = maxMp_;
}

bool MpBar::Update(){
	return false;
}

void MpBar::Draw(){
	for (int i = 4; i < (int)MpLabel::kNumOfLabels; i++) {
		sprites_[i]->Draw();
	}
}

void MpBar::AdjustMP(){
	costTimer_ += kDuration_;

	if (sprites_[(int)MpLabel::kCost]->GetSize().x > sprites_[(int)MpLabel::kMp]->GetSize().x) {
		currentMp_ = (float)std::lerp(currentMp_, targetMp_, Easing::GetInstance()->InSine(costTimer_));

		//Vector2型に変更
		Vector2 adjustedMp{
			currentMp_,
			sprites_[(int)MpLabel::kMp]->GetSize().y
		};

		sprites_[(int)MpLabel::kCost]->SetSize(adjustedMp);
	}
}

void MpBar::UsedMP(){
	if (sprites_[(int)MpLabel::kMp]->GetSize().x > 14 && !isCasted_) {
		Vector2 targetMp{
			(float)sprites_[(int)MpLabel::kMp]->GetSize().x - 50,
			(float)sprites_[(int)MpLabel::kMp]->GetSize().y //変化なし
		};

		//Mpを使い切ってない確認
		if (targetMp.x <= 14) {
			targetMp.x = 14; //14は画像のサイズなので14は0と一緒。
			sprites_[(int)MpLabel::kMp]->SetColor({});
			sprites_[(int)MpLabel::kCost]->SetColor({});
			isEmpty_ = true;
		}

		//Mpを更新
		sprites_[(int)MpLabel::kMp]->SetSize(targetMp);
		//AdjustMP()準備
		targetMp_ = targetMp.x;
		//タイマー開始縦鼻
		coolDownTimer_ = 120;
		costTimer_ = 0;
		//Mpを使用したフラグ
		isCasted_ = true;
	}
}

void MpBar::CoolDown(){
	coolDownTimer_--;
	if (coolDownTimer_ < coolDownDuration) {
		//coolDownTimerによってダメージを受けないようにする
		isCasted_ = false;
	}
}

void MpBar::DebugWindow(){
#ifdef _DEBUG
	ImGui::Begin("MpBar");
	ImGui::Text("frame.%f", costTimer_);
	ImGui::Text("second.%f", kDuration_);
	ImGui::Text("coolDownTimer_.%f", coolDownTimer_);
#endif //_DEBUG
}

