#include "ResultScene.h"
#include "TextureManager.h"
#include <cassert>

ResultScene::ResultScene() {}

ResultScene::~ResultScene() {}

void ResultScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// フェード
	fade_ = make_unique<Fade>();                       // フェードの生成
	fade_->Initialize();                               // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTimer); // フェードイン初期化
}

void ResultScene::Update() {

	switch (phase_) {
	case ResultState::kFadeIn:

		fade_->Update();

		if (fade_->IsFinished()) {
			phase_ = ResultState::kMain;
		}

		if (input_->TriggerKey(DIK_ESCAPE)) {
			phase_ = ResultState::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTimer);
		}

		break;
	
	case ResultState::kMain:
		
		if (input_->TriggerKey(DIK_ESCAPE)) {
			phase_ = ResultState::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTimer);
		}

		break;

	case ResultState::kFadeOut:

		fade_->Update();
		if (fade_->IsFinished()) {
			isFinished_ = true;
		}

		break;

	}

}

void ResultScene::Draw() {

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

bool ResultScene::IsFinished() const { return this->isFinished_; }

void ResultScene::SetIsFinished(const bool& isFinished) { this->isFinished_ = isFinished; }

