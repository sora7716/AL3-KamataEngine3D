#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {

}

GameScene::~GameScene() { 
	delete sprite_; //メモリの削除

	delete model_;

	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//2Dモデル
	textureHandle2D_ = TextureManager::Load("kamata.ico");//テクスチャの読み込み
	textureHandle3D_ = TextureManager::Load("sample.png");//テクスチャの読み込み
	sprite_=Sprite::Create(textureHandle2D_,{100, 50});//スプライトの生成

	//3Dモデル
	model_ = Model::Create();
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	viewProjection_.Initialize();// ビュープロジェクションの初期化

	//サウンド
	soundDateHandle_ = audio_->LoadWave("mokugyo.wav");//サウンドデータの読み込み
	//audio_->PlayWave(soundDateHandle_);//音声再生
	voiceHandle_ = audio_->PlayWave(soundDateHandle_, true);//音声再生

	//ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)

	debugCamera_ = new DebugCamera((int)screenSize.x, (int)screenSize.y);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {
	//2Dのオブジェクトの移動
	Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);//位置を書き換え

	//サウンドの停止
	if (input_->TriggerKey(DIK_SPACE)) {
		if (audio_->IsPlaying(voiceHandle_)) {
		audio_->StopWave(voiceHandle_);//音声の停止
		} else {
			voiceHandle_ = audio_->PlayWave(soundDateHandle_,true);
		}
	}

#ifdef _DEBUG

	//でバックウィンドウの表示
	ImGui::Begin("Debug1");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);//デバックテキストに表示
	ImGui::End();

	ImGui::Begin("Debug2");
	ImGui::InputFloat3("inputFloat3", inputFloat3);               // float3入力ボックス
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f); // float3スライダー
	ImGui::End();

	ImGui::ShowDemoWindow();

	debugCamera_->Update();

#endif // DEBUG

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
	sprite_->Draw();

	PrimitiveDrawer::GetInstance()->DrawLine3d({0,0,0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle3D_);

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
