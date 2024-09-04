#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "imgui.h"

//コンストラクタ
GameScene::GameScene() {}

//デストラクタ
GameScene::~GameScene() {}

//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();

	//クリエイト
	create_ = make_unique<Create>();//クリエイトクラスの生成
	create_->ModelCreate();//モデルの生成
	create_->TextureCreate();//テクスチャの生成

	//プレイヤー
	player_ = make_unique<Player>();
	player_->Initialize(create_->GetModel(create_->typePlayer), &viewProjection_);

	//デバッグカメラ
	debugCamera_ = make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);

#ifdef _DEBUG
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
#endif // _DEBUG

}

//更新
void GameScene::Update() {

	///プレイヤー
	player_->Update();

	///デバッグカメラ
	DebugCameraMove();

}

//描画
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

	///プレイヤー
	player_->Draw();

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

void GameScene::DebugCameraMove() {

	// デバッグカメラの更新
	debugCamera_->Update();

#ifdef _DEBUG
	//Back_spaceキーが押された瞬間
	if (input_->TriggerKey(DIK_BACKSPACE)){	
		//デバッグカメラを有効
		isDebugCameraActive_ ^= true;
	}
#endif // DEBUG

	//デバッグカメラが有効の場合
	if (isDebugCameraActive_) {

		//デバッグカメラからビュー行列とプロジェクション行列のコピー
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新
		viewProjection_.UpdateMatrix();
	}

}