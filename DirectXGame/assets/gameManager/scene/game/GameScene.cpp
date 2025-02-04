#include "GameScene.h"

// デストラクタ
GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize(Create* create) {
	// 初期化
	IScene::Initialize(create);
	// ハニカム
	honeycomb_ = std::make_unique<Honeycomb>();
	honeycomb_->Initialize(&viewProjection_, std::move(create->GetEnvModel()[(int)Create::Env::kGround]));

	// プレイヤー
	player_ = std::make_unique<Player>();                                       // プレイヤーを生成
	playerModel_ = std::make_shared<PlayerModel>();                             // モデルを生成
	player_->SetPlayerModel(std::move(playerModel_));                           // モデルを設定
	player_->Initialize(&viewProjection_, std::move(create->GetPlayerModel())); // プレイヤーの初期化
}

// 更新
void GameScene::Update() {
	// カメラの更新
	(camera_.get()->*Camera::updateTable[cameraMode_])();
	camera_->SetTarget(player_->GetWorldTransform());
	// 更新
	IScene::Update();
	// ハニカム
	honeycomb_->Update();
	// プレイヤー
	player_->Update();
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

	// ハニカム
	honeycomb_->Draw();
	// プレイヤー
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
