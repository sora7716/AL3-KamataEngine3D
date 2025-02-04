#include "GameScene.h"

// デストラクタ
GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize(Create* create) {
	//初期化
	IScene::Initialize(create);
	//ハニカム
	honeycomb_ = std::make_unique<Honeycomb>();
	honeycomb_->Initialize(&viewProjection_, create->GetEnvModel()[(int)Create::Env::kGround]);
}

// 更新
void GameScene::Update() {
	// カメラの更新
	(camera_.get()->*Camera::updateTable[cameraMode_])();
	//更新
	IScene::Update(); 
	//ハニカム
	honeycomb_->Update();
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
	
	//ハニカム
	honeycomb_->Draw();

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
