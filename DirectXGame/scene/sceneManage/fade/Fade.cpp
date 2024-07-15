#include "Fade.h"
#include "TextureManager.h"
#include "WinApp.h"
#define oneFrame 1.0f / 60.0f;
#include <algorithm>
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


// コンストラクター
Fade::Fade() {}

// デストラクター
Fade::~Fade() {}

// 初期化
void Fade::Initialize() {
	textureHandle_ = TextureManager::Load("white1x1.png");
	sprite_ = Sprite::Create(textureHandle_, {}, {}, {});
	sprite_->SetSize(Vector2((float)WinApp::kWindowWidth, (float)WinApp::kWindowHeight));
	sprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

// 更新
void Fade::Update() {
	switch (status_) {
	case Status::None:
		// 何もしない
		break;
	case Status::FadeIn:
		// フェードインの処理
		FadeIn();
		break;
	case Status::FadeOut:
		// フェードアウトの処理
		FadeOut();
		break;
	}
	//ImGui::Text("%f", counter_);
}

// 描画
void Fade::Draw(ID3D12GraphicsCommandList* cmdList) {
	//早期リターン
	if (status_ == Status::None) {
		return;
	}
	sprite_->PreDraw(cmdList, Sprite::BlendMode::kNormal);
	sprite_->Draw();
	sprite_->PostDraw();
}

void Fade::FadeStart(Status status, float duration) {
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::FadeStop() { status_ = Status::None; }

bool Fade::IsFinished() const {
//フェード状態による分岐
	switch (status_) { 
	case Status::FadeIn:
	case Status::FadeOut:
		if (counter_ >= duration_) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}

// フェードアウトの処理
void Fade::FadeOut() {
	// 1フレーム分の秒数をカウントアップ
	counter_ += oneFrame;
	// フェードの継続時間に行ったら打ち止め
	if (counter_ >= duration_) {
		counter_ = duration_;
	}
	// 0.0fから1.0fの間で、継続時間がフェードの継続時間に近づくほどアルファ値を大きくする
	float alpha = std::clamp(counter_ / duration_, 0.0f, 1.0f);
	sprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, alpha));
}

// フェードインの処理
void Fade::FadeIn() {
	// 1フレーム分の秒数をカウントアップ
	counter_ += oneFrame;
	// フェードの継続時間に行ったら打ち止め
	if (counter_ >= duration_) {
		counter_ = duration_;
	}
	// 0.0fから1.0fの間で、継続時間がフェードの継続時間に近づくほどアルファ値を大きくする
	float alpha = 1.0f - std::clamp(counter_ / duration_, 0.0f, 1.0f);
	sprite_->SetColor(Vector4(0.0f, 0.0f, 0.0f, alpha));
}
