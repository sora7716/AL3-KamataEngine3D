#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "calculate/Math.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete modelBlock_;//Blockの3Dモデルの削除

	//拡張for文
	for (std::vector<WorldTransform*> &worldTransformBlockLine :blocks_->GetBlocks()) {//&を付けることで値を参照して使えるようにしている(&を付けないと値がコピーされたものしか取り出せなくなるのでオリジナルをdeleteできない)
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;//配列の中身を削除
		}
	}
	blocks_->GetBlocks().clear(); // 配列の箱自体を削除

	delete debugCamera_;//デバックカメラの削除

	delete skydome_;//スカイドームの削除
	delete modelSkydome_;//スカイドームモデルの削除

	delete player_;//プレイヤーの削除
	delete modelPlayer_;//プレイヤーのモデルの削除

	delete mapChipField_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);//デバックカメラの生成
	debugCamera_->SetFarZ(2000);//farClipの変更
	
	modelPlayer_ = Model::Create();//プレイヤーのモデルの生成
	playerTextureHandle_ = TextureManager::Load("cube/cube.jpg");//プレイヤーのテクスチャ

	player_ = new Player;//プレイヤークラスの生成
	player_->Initialize(modelPlayer_, playerTextureHandle_, &viewProjection_);//プレイヤーの初期化

	skydome_ = new Skydome;//スカイドームの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);//モデルの読み込み(obj)
	skydome_->Initialize(modelSkydome_, &viewProjection_);//スカイドームの初期化

    mapChipField_ = new MapChipField();
	mapChipField_->LoadMapChipCsv("Resources/map/map.csv");
	GenerateBlocks();
}

void GameScene::Update() {
	blocks_->Update();//ブロック
	debugCamera_->Update();
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_BACK)) {
		isDebugCameraActive_ ^= true;
	}
	#endif
	//カメラの処理
	if (isDebugCameraActive_) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	player_->Update();//プレイヤー
}

void GameScene::Draw() {

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
	player_->Draw();//プレイヤー

	blocks_->Draw();//ブロック

	skydome_->Draw();//スカイドーム
	

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

void GameScene::GenerateBlocks() {
	modelBlock_ = Model::Create();                            // ブロックのモデル生成
	blockTextureHandle_ = TextureManager::Load("kamata.ico"); // ブロックのテクスチャ
	viewProjection_.Initialize();                             // ブロックの初期化
	//viewProjection_.farZ = 2000;
	blocks_ = new Blocks;                                                    // ブロックの生成
	blocks_->Initialize(modelBlock_, blockTextureHandle_, &viewProjection_,mapChipField_); // ブロックの初期化
}
