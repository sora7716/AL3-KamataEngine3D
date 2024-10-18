#include "BattleScene.h"
using namespace std;

// デストラクタ
BattleScene::~BattleScene() {}

// 初期化
void BattleScene::Initialize() { 
	//OBB
	obb_ = std::make_unique<OBB>();//生成
	obbMaterial_ = {
	    .center{},
	};
	obb_->Initialize(&viewProjection_,move(obbMaterial_));//初期化
	//六角形
	hexagon_ = std::make_unique<Hexagon>();
	hexagon_->Initialize(create_->GetModel(create_->typeHexagon),&viewProjection_);
}

// 更新
void BattleScene::Update() {
	// デバックカメラの更新
	DebugCameraMove();

	// カメラの更新
	railCamera_->Update();
	//OBB
	obb_->Update();
	ImGui::Begin("wireFrame");
	obb_->DebagText();
	ImGui::End();

	//六角形
	hexagon_->Update();
}

// 描画
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
	
	//OBB
	obb_->Draw();

	//六角形
	hexagon_->Draw();

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
