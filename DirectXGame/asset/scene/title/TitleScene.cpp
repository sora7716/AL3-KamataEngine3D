#include "TitleScene.h"
#include "Input.h"
#include "TextureManager.h"

#include "AxisIndicator.h"
#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>;

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// コンストラクタ
TitleScene::TitleScene() { isFinished_ = false; }

// デストラクタ
TitleScene::~TitleScene() {}

// 初期化
void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();    // ビュープロジェクションの初期化
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成

	fade_ = make_unique<Fade>();                       // フェードの生成
	fade_->Initialize();                               // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTime); // フェードイン初期化

	// レールカメラ
	railCamera_ = make_unique<RailCamera>();                                                                             // 生成
	railCameraWorldTransform_.Initialize();                                                                              // ワールドトランスフォームの初期化
	railCamera_->Initialize(railCameraWorldTransform_.matWorld_, railCameraWorldTransform_.rotation_, &viewProjection_); // 初期化

	// プレイヤー
	player_ = make_unique<Player>();
	player_->InitializeTitle(create_.get(), &viewProjection_);
	player_->SetPearent(&railCamera_->GetWorldTransform());

#pragma region デバックカメラ
	debugCamera_ = make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
#ifdef _DEBUG
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
#endif // _DEBUG
#pragma endregion
}

// 更新
void TitleScene::Update() { ChangePhaseUpdate(); }

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

	// プレイヤー
	player_->Draw();

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
	// レールカメラ
	railCamera_->Update();
	// デバックカメラ
	DebugCameraMove();
	// プレイヤーの更新
	player_->Update();
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

// デバックカメラの操作
void TitleScene::DebugCameraMove() {
#ifdef _DEBUG
	debugCamera_->Update(); // デバックカメラの更新
	if (input_->TriggerKey(DIK_UP)) {
		isDebugCameraActive_ ^= true;
	}
#endif // _DEBUG

	if (isDebugCameraActive_) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		// 行列の更新
		viewProjection_.TransferMatrix();
	}
}
