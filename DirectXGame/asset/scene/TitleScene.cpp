#include "TitleScene.h"
#include "Input.h"
#include "TextureManager.h"

#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>;

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// コンストラクタ
TitleScene::TitleScene() { finished_ = false; }

// デストラクタ
TitleScene::~TitleScene() {
	delete titleFontModel_;
	delete fade_; // フェードの削除
}

// 初期化
void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	titleFontModel_ = Model::CreateFromOBJ("titleFont", true);
	titleFontTextureHandle_ = TextureManager::Load("white1x1.png");
	titleFontWorldTransform_.Initialize();
	titleFontWorldTransform_.rotation_.x = -(std::numbers::pi_v<float> / 2.0f);
	viewProjection_.Initialize();
	fade_ = new Fade();  // フェードの生成
	fade_->Initialize(); // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTime);
}

// 更新
void TitleScene::Update() {
	ChangePhaseUpdate();
#ifdef _DEBUG
	// ImGui::DragFloat("Y", &positionY_);
#endif // _DEBUG
}

// 描画
void TitleScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// タイトルフォント
	titleFontModel_->Draw(titleFontWorldTransform_, viewProjection_, titleFontTextureHandle_);

	// フェード
	fade_->Draw(commandList);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// 終了フラグのゲッター
bool TitleScene::IsFinished() const { return finished_; }

// 終了フラグのセッター
void TitleScene::SetIsFinished(const bool& isFinished) { finished_ = isFinished; }

// 更新処理のフェーズの変更
void TitleScene::ChangePhaseUpdate() {
	switch (phase_) {
	case Phase::kFadeIn:
		// フェードイン
		fade_->Update(); // フェードの更新処理
		TitleFontUpdate();
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
		}

		break;
	case Phase::kMain:
		// メインの処理
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
		}
		TitleFontUpdate();
		break;
	case Phase::kFadeOut:
		// フェードアウト
		fade_->Update();
		TitleFontUpdate();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
	
	
}

//タイトルフォントの更新処理
void TitleScene::TitleFontUpdate() {
	width_ = 1;
	if (positionY_ < 20.0f) {
		positionY_ += 10.0f;
	}
	titleFontWorldTransform_.translation_.y = width_ * sin(theta_) - (titleFontWorldTransform_.translation_.y - positionY_);
	theta_ += std::numbers::pi_v<float> / 30.0f;
	titleFontWorldTransform_.rotation_.y += 0.01f;
	titleFontWorldTransform_.UpdateMatrix();
}
