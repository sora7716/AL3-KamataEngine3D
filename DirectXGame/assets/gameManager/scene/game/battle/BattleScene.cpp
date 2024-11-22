#include "BattleScene.h"
using namespace std;

// デストラクタ
BattleScene::~BattleScene() {}

// 初期化
void BattleScene::Initialize() { 
	//OBB
	obb_ = make_unique<OBB>();//生成
	obbMaterial_ = {
	  .center{0.0f,0.0f,0.0f},
	};
	obb_->Initialize(&viewProjection_,move(obbMaterial_));//初期化
	//六角形
	hexagon_ = make_unique<Hexagon>();
	hexagonMatrial_ = {
	    .center{},
	};
	hexagon_->Initialize(&viewProjection_, move(hexagonMatrial_));

	// マップチップ
	mapChipField_ = make_unique<MapChipField>();
	mapChipField_->LoadMapChipCsv("Resources/map/map.csv");
	//六角形
	honeycomb_ = make_unique<Honeycomb>();
	honeycomb_->Initialize(create_->GetModel(create_->typeHexagon),&viewProjection_,mapChipField_.get());
	

	worldTransform_.Initialize();
	worldPos_ = {worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]};
}

// 更新
void BattleScene::Update() {
	// デバックカメラの更新
	DebugCameraMove();

	// カメラの更新
	railCamera_->Update();
	//OBB
	obb_->Update();
	//六角形
	hexagon_->Update();

	ImGui::Begin("wireFrame");
	obb_->DebagText();
	ImGui::DragFloat3("boxTransform", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
	worldPos_ = {worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1], worldTransform_.matWorld_.m[3][2]};
	//ハニカム
	honeycomb_->Update();
	obb_->DebagText();
	hexagon_->DebugText();
	worldTransform_.UpdateMatrix();
}

void BattleScene::Draw() {

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
	//OBB
	//obb_->Draw();
	//hexagon_->Draw();

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
