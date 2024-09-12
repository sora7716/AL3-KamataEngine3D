#include "ResultScene.h"
#include "TextureManager.h"
#include <cassert>
#include "asset/scene/game/GameScene.h"
#include "asset/math/easing/Easing.h"

#ifdef _DEBUG
#include <imgui.h>
using namespace ImGui;
#endif // _DEBUG


ResultScene::ResultScene() {}

ResultScene::~ResultScene() {}

void ResultScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.Initialize();

	// フェード
	fade_ = make_unique<Fade>();                       // フェードの生成
	fade_->Initialize();                               // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTimer); // フェードイン初期化

	score_ = make_unique<Score>();
	score_->Initialize();

	worldTransform_.Initialize();
	worldTransform_.translation_.x = -720.f;
	worldTransform_.scale_.x = 142.f;
	worldTransform_.scale_.y = 224.f;
	score_->SetScale({0, 0});

	create_ = make_unique<Create>();
	create_->ModelCreate();

	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(create_->GetModel(create_->typeResultSkyDome), &viewProjection_);

}

void ResultScene::Update() {
	Vector3 fontPosition = {worldTransform_.translation_.x, 245, 0};

	skyDome_->Update(false, false, true);

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
	
		score_->Update(100);
		score_->SetPosition(fontPosition);
		score_->SetScale({142, 224});
		
		ResultScene::EaseMove();
		
		score_->SetScore(static_cast<int>(gameScore_));

		if (input_->TriggerKey(DIK_ESCAPE)) {
			phase_ = ResultState::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTimer);
		}

		break;

	case ResultState::kFadeOut:

		score_->Update(100);
		score_->SetPosition(fontPosition);
		score_->SetScale({142, 224});

		ResultScene::EaseMoveOut();

		score_->SetScore(static_cast<int>(gameScore_));

		fade_->Update();
		if (fade_->IsFinished()) {
			isFinished_ = true;
		}

		break;

	}
	worldTransform_.UpdateMatrix();
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

	skyDome_->Draw();

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

	score_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void ResultScene::EaseMove() {

	static float frame = 0;

	static float endFrame = 120;

	if (frame != endFrame) {
		++frame;
	}

	float easing = Easing::OutBounce(frame / endFrame);

	static float begin = worldTransform_.translation_.x;
	static float end = 280;

	worldTransform_.translation_.x = Math::Lerp(begin, end, easing);

}

void ResultScene::EaseMoveOut() {

	static float frame = 0;

	static float endFrame = 100;

	if (frame != endFrame) {
		++frame;
	}

	float easing = Easing::InBack(frame / endFrame);

	static float begin = worldTransform_.translation_.x;
	static float end = 1300;

	worldTransform_.translation_.x = Math::Lerp(begin, end, easing);

}

bool ResultScene::IsFinished() const { return this->isFinished_; }

void ResultScene::SetIsFinished(const bool& isFinished) { this->isFinished_ = isFinished; }

