#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG
#include "assets/math/collision/Collision.h"

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

	// 六角形
	hexagon_ = std::make_unique<Hexagon>();
	hexagon_->Initialize(create_->GetModel(create_->typeHexagon), &viewProjection_);

	worldTransform_.Initialize();
	worldTransform_.translation_.z = 20;

	model[0] = Model::CreateFromOBJ("kibaUe", true);
	model[1] = Model::CreateFromOBJ("kibaSita", true);
	model[2] = Model::CreateFromOBJ("karada", true);
	model[3] = Model::CreateFromOBJ("sita", true);
	model[4] = Model::CreateFromOBJ("atama", true);
	model[5] = Model::CreateFromOBJ("butubutu", true);
	worldTransform.Initialize();
	worldTransform.translation_.z = 10;
	worldTransform.rotation_.x = -std::numbers::pi_v<float> / 2.0f;
}

// 更新
void GameScene::Update() {
	// デバックカメラの更新
	DebugCameraMove();
	// 六角形の更新
	// hexagon_->Update();
	// カメラの更新
	railCamera_->Update();

	ImGui::Begin("box");
	ImGui::DragFloat3("traslation", &worldTransform_.translation_.x, 0.1f);
	ImGui::Text("worldPosX:%f", worldPos_.x);
	ImGui::Text("worldPosY:%f", worldPos_.y);
	ImGui::Text("worldPosZ:%f", worldPos_.z);
	ImGui::End();
	worldTransform_.UpdateMatrix();
	worldPos_ = {worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]};

	ImGui::Begin("mimic");
	ImGui::DragFloat3("rotation", &worldTransform.rotation_.x, 0.1f);
	ImGui::DragFloat3("traslation", &worldTransform.translation_.x, 0.1f);
	ImGui::End();
	worldTransform.UpdateMatrix();
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

	// 六角形
	/*hexagon_->Draw();
	Collision::DrawBox(worldPos_, {1, 1, 1}, &viewProjection_,BLACK);*/

	//トミック
	model[0]->Draw(worldTransform, viewProjection_);
	model[1]->Draw(worldTransform, viewProjection_);
	model[2]->Draw(worldTransform, viewProjection_);
	model[3]->Draw(worldTransform, viewProjection_);
	model[4]->Draw(worldTransform, viewProjection_);
	model[5]->Draw(worldTransform, viewProjection_);
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
