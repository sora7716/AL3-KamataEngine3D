#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "func/Math.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete modelBlock_;//Blockの3Dモデルの削除

	//拡張for文
	for (std::vector<WorldTransform*> &worldTransformBlockLine : worldTransformBlocks_) {//&を付けることで値を参照して使えるようにしている(&を付けないと値がコピーされたものしか取り出せなくなるのでオリジナルをdeleteできない)
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;//配列の中身を削除
		}
	}
	worldTransformBlocks_.clear();//配列の箱自体を削除

	delete debugCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	modelBlock_ = Model::Create();//Blockの3Dモデルの生成
	blockTextureHandle_ = TextureManager::Load("kamata.ico");
	viewprojection_.Initialize();

	//要素数
	const uint32_t kNumBlockVirtical   = 10;
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック1個分の横幅
	const float kBlockHeight = 2.0f;
	const float kBlockWidth  = 2.0f;
	//要素数の変更
	worldTransformBlocks_.resize(kNumBlockVirtical);//縦の行(配列)
	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);//上で決めた行を横に伸ばす(配列)
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			//初期化↓
			if (i % 2 == 1 && j % 2 == 1 || i % 2 == 0 && j % 2 == 0) {
				worldTransformBlocks_[i][j] = new WorldTransform();//ブロックの生成
				worldTransformBlocks_[i][j]->Initialize();//ブロックの初期化
				worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;//横にj分ずらす
				worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;//縦にi分ずらす
			}
			//初期化↑
		}
	}
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);//デバックカメラの生成
}

void GameScene::Update() {
	for (std::vector<WorldTransform*>&worldTransformBlockLine:worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) { continue; }
			worldTransformBlock->UpdateMatrix();//アフィン変換
		}
	}
	debugCamera_->Update();
	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)&&!isDebugCameraActive_) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_SPACE)&&isDebugCameraActive_) {
		isDebugCameraActive_ = false;
	}
	#endif
	//カメラの処理
	if (isDebugCameraActive_) {
		viewprojection_.matView = debugCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewprojection_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新と転送
		viewprojection_.UpdateMatrix();
	}
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
	for (std::vector<WorldTransform*>& worldTransformBlockLine:worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) { continue; }
			modelBlock_->Draw(*worldTransformBlock, viewprojection_/*, blockTextureHandle_*/);//ブロックの描画
		}
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
