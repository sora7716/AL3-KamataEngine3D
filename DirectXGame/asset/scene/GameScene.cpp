#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include "WinApp.h"
#include <cassert>

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ゲームシーン
	viewProjection_.Initialize();
	// クリエイトクラス
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成
	create_->TextureCreate();        // テクスチャを生成

	// プレイヤークラス
	Create::ObjectType typePlayer = Create::Type::kPlayer;
	player_ = make_unique<Player>(); // 生成
	player_->Initialize(create_->GetModel(typePlayer), &viewProjection_, create_->GetTextureHandle(typePlayer));

	//敵のクラス
	Create::ObjectType typeEnemy = Create::Type::kEnemy;
	enemy_ = make_unique<Enemy>();
	enemy_->Initialize(create_->GetModel(typeEnemy), &viewProjection_, create_->GetTextureHandle(typeEnemy), {0,3,100});
	enemy_->SetPlayer(player_.get());
	// キー入力のコマンドの初期化
	InputCommandInitialize();

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
void GameScene::Update() {

	// プレイヤー
	player_->Update();     // 更新処理
	PlayerActionCommand(); // 移動のコマンド

	//敵
	enemy_->Update();

	// デバックカメラ
	debugCamera_->Update(); // 更新処理
	DebugCameraMove();      // デバックカメラの動き
}

// 描画
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	//
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
	
	//プレイヤー
	player_->Draw();

	//敵
	if (enemy_) {
		enemy_->Draw();
	}

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

// キー入力のコマンドの初期化
void GameScene::InputCommandInitialize() {
	inputHandle_ = make_unique<InputHandle>();
	inputHandle_->Initialize(input_);
	inputHandle_->AssingMoveLeftCommand2PressKeysLeft();   // 左へ
	inputHandle_->AssingMoveRightCommand2PressKeysRight(); // 右へ
	inputHandle_->AssingMoveDownCommand2PressKeysDown();   // 下へ
	inputHandle_->AssingMoveUpCommand2PressKeysUp();       // 上へ
	inputHandle_->AssingRotateLeftCommand2PressKeyA();     // 左回転
	inputHandle_->AssingRotateRightCommand2PressKeyD();    // 右回転
}

// プレイヤーのコマンドをまとめた
void GameScene::PlayerActionCommand() {
	// 移動
	player_->SetVelocity({});                                          // 速度の初期化
	iPlayerCommandBeside_ = inputHandle_->PlayerBesideMoveInput();     // 横移動
	iPlayerCommandVertical_ = inputHandle_->PlayerVerticalMoveInput(); // 縦移動
	if (iPlayerCommandBeside_) {
		iPlayerCommandBeside_->Exec(*player_); // 横移動
	}
	if (iPlayerCommandVertical_) {
		iPlayerCommandVertical_->Exec(*player_); // 縦移動
	}

	// 旋回
	iPlayerCommandRotate_ = inputHandle_->PlayerRotateInput(); // 旋回
	if (iPlayerCommandRotate_) {
		iPlayerCommandRotate_->Exec(*player_); // 旋回
	}
}

// デバックカメラ
void GameScene::DebugCameraMove() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_BACKSPACE)) {
		isDebugCameraActive_ ^= true;
	}
#endif // _DEBUG

	if (isDebugCameraActive_) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// 行列の更新
		viewProjection_.UpdateMatrix();
	}
}
