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
TitleScene::TitleScene() { isFinished_ = false; }

// デストラクタ
TitleScene::~TitleScene() {
	delete fade_; // フェードの削除
}

// 初期化
void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成

	viewProjection_.Initialize();
	fade_ = new Fade();                                // フェードの生成
	fade_->Initialize();                               // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTime); // フェードイン初期化
}

// 更新
void TitleScene::Update() {
	ChangePhaseUpdate();
#ifdef _DEBUG

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
bool TitleScene::IsFinished() const { return isFinished_; }

// 終了フラグのセッター
void TitleScene::SetIsFinished(const bool& isFinished) { isFinished_ = isFinished; }

// 更新処理のフェーズの変更
void TitleScene::ChangePhaseUpdate() {
	switch (phase_) {
	case Phase::kFadeIn:
		// フェードイン
		fade_->Update(); // フェードの更新処理
		// TitleFontUpdate();
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
		break;
	case Phase::kFadeOut:
		// フェードアウト
		fade_->Update();
		if (fade_->IsFinished()) {
			isFinished_ = true;
		}
		break;
	}
}