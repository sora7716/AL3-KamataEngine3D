#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();

#pragma region デバックカメラ
	debugCamera_ = std::make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
#ifdef _DEBUG
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
#endif // _DEBUG
#pragma endregion

	// クリエイト
	create_ = std::make_unique<Create>(); // クリエイトクラスの生成
	create_->ModelCreate();               // モデルの生成
	create_->TextureCreate();             // テクスチャの生成

	// カメラ
	railCamera_ = std::make_unique<RailCamera>();                                                                // レールカメラクラスの生成
	cameraWorldTransform_.Initialize();                                                                          // カメラのワールドトランスフォームの初期化
	railCamera_->Initialize(cameraWorldTransform_.matWorld_, cameraWorldTransform_.rotation_, &viewProjection_); // レールカメラの初期化
	model_.resize(5);
	for (int i = 0; i < 5; i++) {
		model_[i].resize(5);
		for (int j = 0; j < 5; j++) {
			model_[i][j] = create_->GetModel(create_->typeHexagon);
		}
	}
}

// 更新
void GameScene::Update() {
	// デバックカメラの更新
	DebugCameraMove();
	// カメラの更新
	railCamera_->Update();
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
	DrawHoneycombMap();

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

// デバックカメラ
void GameScene::DebugCameraMove() {
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

void GameScene::DrawHoneycombMap() {
	static const int rows= 5;
	static const int cols = 5;
	static int size = 32;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			float xOffset = col * size * 1.5f;
			float yOffset = row * size * sqrtf(3);
			if (col % 2 == 1) {
				yOffset += size * sqrtf(3) / 2; // 奇数列は半分ずらす
			}
			WorldTransform worldTransform;
			worldTransform.Initialize();
			worldTransform.translation_ = {xOffset, yOffset, 0.0f};
			model_[row][col]->Draw(worldTransform, viewProjection_);
		}
	}
}
