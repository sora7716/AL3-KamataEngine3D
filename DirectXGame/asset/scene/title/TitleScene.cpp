#include "TitleScene.h"
#include "Input.h"
#include "TextureManager.h"
#include "asset/scene/game/GameScene.h"

#include "AxisIndicator.h"
#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>;
#include "asset/gameObject/text/SceneText.h"

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
	titleAnimation_->Initialize(player_.get(), railCamera_.get());

	// スカイドーム
	skyDome_ = make_unique<SkyDome>();                                               // 生成
	skyDome_->Initialize(create_->GetModel(create_->typeSkyDome), &viewProjection_); // 初期化
	skyDome_->SetRotation({});                                                       // ローテーションの設定
	skyDome_->SetTranslation({});

	// セレクト画面
	selectScene_ = make_unique<Select>();
	selectScene_->Initialize(player_.get(), railCamera_.get());

	// タイトルフォント
	titleFont_ = make_unique<TitleFont>();                                               // 生成
	titleFont_->Initialize(create_->GetModel(create_->typeTitleFont), &viewProjection_); // 初期化

	// セレクト画面で使用するボタン
	// スタートボタンの背景
	selectButtons_[(int)ISelectButton::typeStart_Back] = make_unique<StartBackButton>();
	selectButtons_[(int)ISelectButton::typeStart_Back]->Initialize(create_->GetModel(create_->typeButtonBack), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeStart_Back]->SetParent(&railCamera_->GetWorldTransform());
	// スタートボタン
	selectButtons_[(int)ISelectButton::typeStart] = make_unique<StartButton>();
	selectButtons_[(int)ISelectButton::typeStart]->Initialize(create_->GetModel(create_->typeStart), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeStart]->SetParent(&selectButtons_[(int)ISelectButton::typeStart_Back]->GetWorldTransform());

	// ルールボタンの背景
	selectButtons_[(int)ISelectButton::typeRule_Back] = make_unique<RuleBackButton>();
	selectButtons_[(int)ISelectButton::typeRule_Back]->Initialize(create_->GetModel(create_->typeButtonBack), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeRule_Back]->SetParent(&railCamera_->GetWorldTransform());
	// ルールボタン
	selectButtons_[(int)ISelectButton::typeRule] = make_unique<RuleButton>();
	selectButtons_[(int)ISelectButton::typeRule]->Initialize(create_->GetModel(create_->typeRule), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeRule]->SetParent(&selectButtons_[(int)ISelectButton::typeRule_Back]->GetWorldTransform());
	// セレクトする用のボタン
	selectButtons_[(int)ISelectButton::typeSelectButton] = make_unique<SelectButton>();
	selectButtons_[(int)ISelectButton::typeSelectButton]->Initialize(create_->GetModel(create_->typeSelectButton), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectButton]->SetParent(&railCamera_->GetWorldTransform());
	// セレクトキー(W)の背景
	selectButtons_[(int)ISelectButton::typeSelectKeyW_Back] = make_unique<SelectKeyW_Back>();
	selectButtons_[(int)ISelectButton::typeSelectKeyW_Back]->Initialize(create_->GetModel(create_->typekeyW_Back), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectKeyW_Back]->SetParent(&selectButtons_[(int)ISelectButton::typeStart_Back]->GetWorldTransform());
	// セレクトキー(W)の文字
	selectButtons_[(int)ISelectButton::typeSelectKeyW_moji] = make_unique<SelectKeyW_Moji>();
	selectButtons_[(int)ISelectButton::typeSelectKeyW_moji]->Initialize(create_->GetModel(create_->typekeyW_Moji), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectKeyW_moji]->SetParent(&selectButtons_[(int)ISelectButton::typeSelectKeyW_Back]->GetWorldTransform());
	// セレクトキー(S)の背景
	selectButtons_[(int)ISelectButton::typeSelectKeyS_Back] = make_unique<SelectKeyS_Back>();
	selectButtons_[(int)ISelectButton::typeSelectKeyS_Back]->Initialize(create_->GetModel(create_->typekeyS_Back), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectKeyS_Back]->SetParent(&selectButtons_[(int)ISelectButton::typeRule_Back]->GetWorldTransform());
	// セレクトキー(S)の文字
	selectButtons_[(int)ISelectButton::typeSelectKeyS_moji] = make_unique<SelectKeyS_Moji>();
	selectButtons_[(int)ISelectButton::typeSelectKeyS_moji]->Initialize(create_->GetModel(create_->typekeyS_Moji), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectKeyS_moji]->SetParent(&selectButtons_[(int)ISelectButton::typeSelectKeyS_Back]->GetWorldTransform());
	// セレクトキー(ESC)の背景
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Back] = make_unique<SelectKeyESC_Back>();
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Back]->Initialize(create_->GetModel(create_->typekeyESC_Back), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Back]->SetParent(&railCamera_->GetWorldTransform());
	// セレクトキー(ESC)の文字
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Moji] = make_unique<SelectKeyESC_Moji>();
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Moji]->Initialize(create_->GetModel(create_->typekeyESC_Moji), &viewProjection_);
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Moji]->SetParent(&selectButtons_[(int)ISelectButton::typeSelectKeyESC_Back]->GetWorldTransform());

	// シーンテキスト
	sceneText_ = make_unique<SceneText>();                                               // 生成
	sceneText_->Initialize(create_->GetModel(create_->typeSceneText), &viewProjection_); // 初期化
	sceneText_->SetParent(&railCamera_->GetWorldTransform());                            // 親子付け
	sceneText_->SetPosition({-0.2f, -3.51f, 0.0f});                                      // 位置を0に設定

	worldTransform_.Initialize();
	worldTransform_.translation_.y = -3.3f;

	// BGM
	soundDataHandle_ = audio_->LoadWave("sound/BGM/title1.wav"); // 読み込み
	soundPlayHandle_ = audio_->PlayWave(soundDataHandle_, true); // 再生
	audio_->SetVolume(soundDataHandle_, 0.5f);

	// SE(SPACEキー押したとき)
	seDateHandle_[0] = audio_->LoadWave("sound/SE/button1.mp3");
	seDateHandle_[1] = audio_->LoadWave("sound/SE/select1.mp3");
	seDateHandle_[2] = audio_->LoadWave("sound/SE/esc.mp3");

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
	// 更新処理のフェーズ管理
	ChangePhaseUpdate();
	// スペースを押せのやつ
	PressSpaceMove();
#ifdef _DEBUG
	ImGui::Begin("titleScene");
	ImGui::Text("phase%d", phase_);
	ImGui::End();
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

	// スカイドーム
	skyDome_->Draw();

	// プレイヤー
	player_->Draw();

	// タイトルフォント
	titleFont_->Draw();

	// セレクトボタンボタン
	for (auto& selectButton : selectButtons_) {
		selectButton->Draw();
	}

	sceneText_->Draw();
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

void TitleScene::BGMStop() { audio_->StopWave(soundPlayHandle_); }

// 更新処理のフェーズの変更
void TitleScene::ChangePhaseUpdate() {
	// プレイヤーのアニメーション
	titleAnimation_->Update(selectScene_->IsHome());

	// ホームじゃなかったら
	if (!selectScene_->IsHome()) {
		SetPartisPositionAndAngle();           // パーツの角度やポジションを元に戻す
		player_->SetScale({1.0f, 1.0f, 1.0f}); // プレイヤーの大きさを元に戻す
	}
	// タイトルフォントの更新
	titleFont_->Update();
	// レールカメラ
	railCamera_->Update();
	// デバックカメラ
	DebugCameraMove();
	// スカイドーム
	skyDome_->Update(false, true);
	// セレクトボタンの更新処理をまとめた
	SelectButtonUpdate();

	switch (phase_) {
	case Phase::kFadeIn:
		// プレイヤーの更新
		player_->Update(0, true);
		// フェードイン
		fade_->Update(); // フェードの更新処理
		// TitleFontUpdate();
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		// セレクト画面
		GameStart();
		// クリックしたときの音
		PressButtonSE();

		break;
	case Phase::kMain:
		// クリックしたときの音
		PressButtonSE();
		// プレイヤーの更新
		player_->Update(0, true);
		// セレクト画面
		GameStart();
		break;
	case Phase::kAnimation:

		// プレイヤーの更新
		player_->Update(0, true);
		if (titleAnimation_->IsChangeGameScene()) {
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);//フェードをスタートさせるか
			phase_ = Phase::kFadeOut;//フェードアウトに変更
		}
		break;
	case Phase::kFadeOut:

		// フェードアウト
		fade_->Update(WHITE);
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

void TitleScene::PressButtonSE() {

	if (input_->TriggerKey(DIK_SPACE)) {
		sePlayHandle_[0] = audio_->PlayWave(seDateHandle_[0], false);
	}

	if (input_->TriggerKey(DIK_W) && selectScene_->IsMoveSelect()) {
		sePlayHandle_[1] = audio_->PlayWave(seDateHandle_[1], false);
	}

	if (input_->TriggerKey(DIK_S) && selectScene_->IsMoveSelect()) {
		sePlayHandle_[1] = audio_->PlayWave(seDateHandle_[1], false);
	}

	if (input_->TriggerKey(DIK_ESCAPE)) {
		sePlayHandle_[2] = audio_->PlayWave(seDateHandle_[2], false);
	}
}

// スペースを押せのフォントの動き
void TitleScene::PressSpaceMove() {
	sceneText_->Update();
	float beginPos = 0.0f;
	float endPos = 12.51f;
	float endFrame = 60;
	static float result = 0.0f;
	if (isTextMove_) {
		if (textFrame_++ > endFrame) {
			textFrame_ = endFrame;
			isTextMove_ = false;
			sceneText_->SetParent(nullptr);
		}
	}
	if (titleFont_->IsGameStartAnimation()) {
		isTextBack_ = true;
	}
	if (isTextBack_) {
		if (textFrame_-- < 0.0f) {
			textFrame_ = 0.0f;
			isTextBack_ = false;
			sceneText_->SetParent(&railCamera_->GetWorldTransform());
		}
	}

	result = Math::Lerp(beginPos, endPos, Easing::InOutCubic(textFrame_ / endFrame));
	sceneText_->SetPosition({
	    sceneText_->GetWorldTransform().translation_.x,
	    sceneText_->GetWorldTransform().translation_.y,
	    result,
	});
}

// セレクトボタンの更新処理をまとめた
void TitleScene::SelectButtonUpdate() {
	// セレクトシーンに遷移
	selectScene_->Update((int)phase_);
	//  セレクトボタンボタン
	for (auto& selectButton : selectButtons_) {
		selectButton->Update();
	}
	// ゲームが始まるときのアニメーションが開始するフラグをセットする
	titleAnimation_->SetIsGameStartAnimation(titleFont_->IsGameStartAnimation());
	// 線形補間のゲッター
	selectButtons_[(int)ISelectButton::typeStart_Back]->SetIsButtonLarp(selectScene_->IsMoveSelect());   // スタートの背景
	selectButtons_[(int)ISelectButton::typeRule_Back]->SetIsButtonLarp(selectScene_->IsMoveSelect());    // ルールの背景
	selectButtons_[(int)ISelectButton::typeSelectButton]->SetIsButtonLarp(selectScene_->IsMoveSelect()); // セレクトボタン
	// フレームのゲッター
	selectButtons_[(int)ISelectButton::typeStart_Back]->SetFrame(selectScene_->GetFrame());   // スタートの背景
	selectButtons_[(int)ISelectButton::typeRule_Back]->SetFrame(selectScene_->GetFrame());    // ルールの背景
	selectButtons_[(int)ISelectButton::typeSelectButton]->SetFrame(selectScene_->GetFrame()); // セレクトボタン
	// 選択したかのセッター
	selectButtons_[(int)ISelectButton::typeStart_Back]->SetIsSelectChangeColor(selectButtons_[(int)ISelectButton::typeSelectButton]->IsSelectStart()); // スタートの背景
	selectButtons_[(int)ISelectButton::typeRule_Back]->SetIsSelectChangeColor(selectButtons_[(int)ISelectButton::typeSelectButton]->IsSelectRule());   // ルールの背景
	
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Back]->SetPhase(static_cast<int>(phase_));
	selectButtons_[(int)ISelectButton::typeSelectKeyESC_Moji]->SetPhase(static_cast<int>(phase_));
}

void TitleScene::GameStart() {
	// メインの処理
	if (selectButtons_[(int)ISelectButton::typeSelectButton]->IsGameStart()) {
		phase_ = Phase::kAnimation;
		// スタートボタンを決定したら
		titleFont_->SetIsSelectGameStart(selectButtons_[(int)ISelectButton::typeSelectButton]->IsGameStart());
	}
}
