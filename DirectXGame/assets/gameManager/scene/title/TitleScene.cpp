#include "TitleScene.h"

// デストラクタ
TitleScene::~TitleScene() {}

// 初期化
void TitleScene::Initialize() {

	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_.reset(Model::Create());

	worldTransform_.Initialize();
}

// 更新
void TitleScene::Update() {

	std::string label = "scale";
	ImGui::DragFloat3(label.c_str(), &worldTransform_.scale_.x, 0.01f);
	label = "rotation";
	ImGui::DragFloat3(label.c_str(), &worldTransform_.rotation_.x, 0.01f);
	label = "translation";
	ImGui::DragFloat3(label.c_str(), &worldTransform_.translation_.x, 0.01f);
	
	
	worldTransform_.UpdateMatrix();

	// デバックカメラの更新
	//DebugCameraMove();

	// カメラの更新
	railCamera_->Update();
}

//描画
void TitleScene::Draw() {

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
	
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	

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

void TitleScene::Animation() {
}