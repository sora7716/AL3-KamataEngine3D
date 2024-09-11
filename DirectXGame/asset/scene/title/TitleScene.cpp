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
void TitleScene::Initialize(bool isSound) {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();    // ビュープロジェクションの初期化
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成

	// フェード
	fade_ = make_unique<Fade>();                       // フェードの生成
	fade_->Initialize();                               // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTime); // フェードイン初期化

	// レールカメラ
	railCamera_ = make_unique<RailCamera>();                                                                             // 生成
	railCameraWorldTransform_.Initialize();                                                                              // ワールドトランスフォームの初期化
	railCamera_->Initialize(railCameraWorldTransform_.matWorld_, railCameraWorldTransform_.rotation_, &viewProjection_); // 初期化

	// プレイヤー
	player_ = make_unique<Player>();                                  // 生成
	player_->Initialize(create_.get(), &viewProjection_);             // 初期化
	player_->SetPosition({0.0f, 0.0f, 20.0f});                        // 位置
	player_->SetRotation({0.0f, -numbers::pi_v<float> / 2.0f, 0.0f}); // 角度
	SetPartisPositionAndAngle();                                      // パーツの角度と位置

	// タイトルのアニメーション
	titleAnimation_ = make_unique<TitleAnimation>();
	titleAnimation_->Initialize(player_.get());

	// スカイドーム
	skyDome_ = make_unique<SkyDome>();                                               // 生成
	skyDome_->Initialize(create_->GetModel(create_->typeSkyDome), &viewProjection_); // 初期化
	skyDome_->SetRotation({});                                                       // ローテーションの設定
	skyDome_->SetTranslation({});

	// セレクト画面
	selectScene_ = make_unique<Select>();
	selectScene_->Initialize(player_.get(),railCamera_.get());

	// BGM
	soundDataHandle_ = audio_->LoadWave("sound/BGM/title1.wav");// 読み込み
	if (isSound) {
		soundPlayHandle_ = audio_->PlayWave(soundDataHandle_, true); // 再生
	}
	

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
void TitleScene::Update() {
	//プレイヤーのアニメーション
	titleAnimation_->Update(selectScene_->IsHome());
	//セレクト画面への遷移
	selectScene_->Update();
	//ホームじゃなかったら
	if (!selectScene_->IsHome()) {
		SetPartisPositionAndAngle();//パーツの角度やポジションを元に戻す
		player_->SetScale({1.0f, 1.0f, 1.0f});//プレイヤーの大きさを元に戻す
	}
	ChangePhaseUpdate();
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

	// スカイドーム
	skyDome_->Draw();

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
	// スカイドーム
	skyDome_->Update(false, false);

	switch (phase_) {
	case Phase::kFadeIn:
		// プレイヤーの更新
		player_->Update();
		// フェードイン
		fade_->Update(); // フェードの更新処理
		// TitleFontUpdate();
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		/*if (Input::GetInstance()->PushKey(DIK_RETURN)) {
			phase_ = Phase::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
		}*/

		break;
	case Phase::kMain:
		// プレイヤーの更新
		player_->Update();
		// メインの処理
		if (Input::GetInstance()->PushKey(DIK_RETURN)) {
			phase_ = Phase::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
		}
		if (Input::GetInstance()->PushKey(DIK_R)) {
			audio_->StopWave(soundPlayHandle_); // BGM停止
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

// パーツの位置と角度のセッターをまとめた
void TitleScene::SetPartisPositionAndAngle() {
	// 位置
	player_->SetPartsPosition(IPlayerParts::head, {0.0f, 1.0f, 0.0f});       // 頭
	player_->SetPartsPosition(IPlayerParts::body, {0.0f, -2.25f, 0.0f});     // 体
	player_->SetPartsPosition(IPlayerParts::arm, {0.0f, -0.98f, 0.0f});      // 腕
	player_->SetPartsPosition(IPlayerParts::left_arm, {0.0f, 0.0f, 2.0f});   // 左腕
	player_->SetPartsPosition(IPlayerParts::right_arm, {0.0f, 0.0f, -2.0f}); // 右腕
	player_->SetPartsPosition(IPlayerParts::ear, {0.0f, 2.0f, 0.0f});        // 耳
	player_->SetPartsPosition(IPlayerParts::left_ear, {-1.5f, 0.0f, 0.0f});  // 左耳
	player_->SetPartsPosition(IPlayerParts::right_ear, {1.5f, 0.0f, 0.0f});  // 右耳
	// 角度
	player_->SetPartsAngle(IPlayerParts::head, {0.0f, numbers::pi_v<float> / 2.0f, 0.0f}); // 頭
	player_->SetPartsAngle(IPlayerParts::body, {0.0f, 0.0f, 0.0f});                        // 体
	player_->SetPartsAngle(IPlayerParts::arm, {0.0f, 0.0f, 0.0f});                         // 腕
	player_->SetPartsAngle(IPlayerParts::left_arm, {0.3f, 5.6f, 2.3f});                    // 左腕
	player_->SetPartsAngle(IPlayerParts::right_arm, {-0.3f, -5.6f, 2.3f});                 // 右腕
	player_->SetPartsAngle(IPlayerParts::ear, {1.0f, 1.5f, 0.0f});                         // 耳
	player_->SetPartsAngle(IPlayerParts::left_ear, {0.0f, 0.0f, 0.0f});                    // 左耳
	player_->SetPartsAngle(IPlayerParts::right_ear, {0.0f, 0.0f, 0.0f});                   // 右耳

	// アニメーションを止める
	player_->SetPartsIsAnimation(IPlayerParts::arm, false); // 腕
}
