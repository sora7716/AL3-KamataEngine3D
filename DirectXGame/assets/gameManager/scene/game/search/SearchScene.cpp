#include "SearchScene.h"

// デストラクタ
SearchScene::~SearchScene() {}

// 初期化
void SearchScene::Initialize(Create* create) {
	//初期化
	IScene::Initialize(create);

	// 天球の生成&初期化
	skyDome_ = std::make_unique<Skydome>();
	skyDome_->Initialize(create_->GetModel(create_->typeSkydome), &viewProjection_);

	// 地面の生成&初期化
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(create_->GetModel(create_->typeGround),&viewProjection_);
}

// 更新
void SearchScene::Update() {
	//更新
	IScene::Update(); 
	skyDome_->Update();
	ground_->Update();
}

// 描画
void SearchScene::Draw() {

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

	skyDome_->Draw();
	ground_->Draw();

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
