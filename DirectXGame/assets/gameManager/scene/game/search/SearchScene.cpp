#include "SearchScene.h"
#include "assets/gameObject/environment/ground/Ground.h"
#include "assets/gameObject/environment/skydome/Skydome.h"
using namespace std;

// デストラクタ
SearchScene::~SearchScene() {}

// 初期化
void SearchScene::Initialize() {
	//スカイドーム
	environments_[(int)Type::kSkydome] = make_unique<Skydome>();
	environments_[(int)Type::kSkydome]->Initialize(&viewProjection_, create_->GetModel(create_->typeSkydome));
	//地面
	environments_[(int)Type::kGround] = make_unique<Ground>();
	environments_[(int)Type::kGround]->Initialize(&viewProjection_, create_->GetModel(create_->typeGround));
	//プレイヤー
	player_= make_unique<Player>();
	player_->Initialize(&viewProjection_, create_->GetPlayerModel(create_->typeHead));
	//追従カメラのビュープロジェクションを受け取る
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 追従対象をセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	isFollowOn = true;//追従on
	//コントローラーの生成
	control_ = make_unique<Controller>();
}

// 更新
void SearchScene::Update() {
	// デバックカメラの更新
	DebugCameraMove();
	//環境の更新
	for (auto& evbiroment : environments_) {
		evbiroment->Update();
	}
	//コントローラのタイプ
	control_->ControlUpdate(player_.get(), followCamera_.get(), (Controller::ControlType)isSelectContorol_);
	//プレイヤーの更新
	player_->Update();
	// カメラの更新
	followCamera_->Update();

#ifdef _DEBUG
	//デバック
	ImGui::Begin("test");
	ImGui::Checkbox("controlType", &isSelectContorol_);
	ImGui::End();
#endif // _DEBUG
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

	//環境の描画
	for (auto& evbiroment : environments_) {
		evbiroment->Draw();
	}
	//プレイヤーの描画
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
