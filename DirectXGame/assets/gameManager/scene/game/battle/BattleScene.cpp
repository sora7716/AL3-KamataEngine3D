#include "BattleScene.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/honeycomb/Honeycomb.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/skydome/Skydome.h"
using namespace std;
// デストラクタ
BattleScene::~BattleScene() {}

// 初期化
void BattleScene::Initialize(Create* create) {
	// 初期化
	IScene::Initialize(create);
	// OBB
	for (int i = 0; i < obbs_.size(); i++) {
		obbs_[i] = std::make_unique<OBB>();                                     // 生成
		obbs_[i]->Initialize({.center = {}, .rotation = {}}, &viewProjection_); // 初期化
	}

	hexagon_ = new Hexagon();
	//  六角形
	hexagon_->Initialize(
	    &viewProjection_, {
	                          .center = {},
                                .size = {1.0f, 0.1f, 1.0f}
    });

	// マップチップ
	mapChipField_ = make_unique<MapChipField>();
	mapChipField_->LoadMapChipCsv("Resources/map/map.csv");

	// スカイドーム
	environments_[(int)Type::kSkydome] = make_unique<Skydome>();
	environments_[(int)Type::kSkydome]->Initialize(create_->GetModel(create_->typeSkydome), &viewProjection_);

	// 地面(ハニカム)
	environments_[(int)Type::kGround] = make_unique<Honeycomb>(mapChipField_.get());
	environments_[(int)Type::kGround]->Initialize(create_->GetModel(create_->typeHexagon), &viewProjection_);

	// プレイヤー
	player_ = make_unique<Player>();
	player_->Initialize(std::move(create_->GetPlayerModel()), &viewProjection_);

	// 追従カメラのビュープロジェクションを受け取る
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 追従対象をセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	followCamera_->SetTarget(player_.get());
	//リセット(瞬間合わせ)
	followCamera_->Reset();
	// カメラ移動範囲
	followCamera_->SetMovableArea({-30, 400, 0, 50});

	isFollowOn = true; // 追従on

	// コントローラーの生成
	controller_ = Controller::GetInstance();
	controller_->Initialize(player_.get(), followCamera_.get());

	// ミミック
	enemy_ = std::make_unique<Mimic>();
	enemy_->Initialize(std::move(create_->GetMimicModel()), &viewProjection_);
	enemy_->SetPlayer(player_.get());

	// 光り輝くパーティクル
	luminous_ = std::make_unique<Luminous>();
	luminous_->Initialize(create_->GetModel(create_->typeParticle), &viewProjection_);
	luminous_->SetDirectionView(&followCamera_->GetViewProjection());

	particle_ = std::make_unique<Particle>();
	particle_->Initialize(create_->GetModel(create_->typeParticle), &viewProjection_);
	particle_->SetParent(&luminous_->GetCenter());
	particle_->SetDirectionView(&followCamera_->GetViewProjection());

	// 球
	for (int i = 0; i < 2; i++) {
		spheres_[i] = std::make_unique<Sphere>();
		spheres_[i]->Initialize(
		    {
		        .center = {0.0f, 0.0f, 5.0f},
                  .radius = 2.0f, .rotation = {}
        },
		    &viewProjection_);
	}

	// サーチライト
	serchlight_ = new Searchlight();
	Shape::SerchlightMaterial mat = {
	    .center{},
	    .direction = 45.0f,
	    .range = 90.0f,
	};
	mat.radius = 5.0f;
	serchlight_->Initialize(std::move(mat), &viewProjection_);
}

// 更新
void BattleScene::Update() {
	// 当たり判定を計算
	CheckCollision();
	// 更新
	IScene::Update();

	// カメラの更新
	railCamera_->Update();
#ifdef _DEBUG
	// 六角形
	hexagon_->Update();

	// OBB
	for (auto& obb : obbs_) {
		obb->Update();
	}

	// 球
	for (auto& sphere : spheres_) {
		sphere->Update();
	}

	serchlight_->Update();

	/*ImGui::Begin("wireFrame");
	spheres_[0]->DebugText("sphere[0]");
	spheres_[1]->DebugText("sphere[1]");
	hexagon_->DebugText();
	obbs_[0]->DebagText("obb[0]");
	obbs_[1]->DebagText("obb[1]");
	serchlight_->DebugText();
	ImGui::End();*/
#endif // _DEBUG

	// 環境の更新
	for (auto& evbiroment : environments_) {
		evbiroment->Update();
	}

	// コントローラのタイプ
	controller_->ControlUpdate((Controller::ControlType)isSelectContorol_);

	// プレイヤーの更新
	player_->Update();
	player_->DebugText("player");

	// カメラの更新
	followCamera_->Update();

	// 敵の更新
	enemy_->Update();

	luminous_->Update();
	luminous_->DebugText();
	particle_->Update();
	particle_->DebugText();
	particle_->SetMove(luminous_->GetMove());
#ifdef _DEBUG
	// デバック
	ImGui::Begin("test");
	ImGui::Checkbox("controlType", &isSelectContorol_);
	ImGui::End();
#endif // _DEBUG
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

	// 環境の描画
	for (auto& evbiroment : environments_) {
		evbiroment->Draw();
	}
	// プレイヤーの描画
	player_->Draw();

	// 敵の描画
	enemy_->Draw();

	luminous_->Draw();
	particle_->Draw();

#ifdef _DEBUG
	// OBB
	/*for (auto& obb : obbs_) {
	    obb->Draw();
	}*/
	// hexagon
	// hexagon_->Draw();
	////球
	/*for (auto& sphere : spheres_) {
	    sphere->Draw();
	}*/
	// serchlight_->Draw();
#endif // _DEBUG
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

// 当たり判定を計算
void BattleScene::CheckCollision() {
	/*spheres_[0]->OnCollision(spheres_[0]->GetSphereMaterial() == spheres_[1]->GetSphereMaterial());
	spheres_[1]->OnCollision(spheres_[0]->GetSphereMaterial() == spheres_[1]->GetSphereMaterial());*/
	/*for (int i = 0; i < obbs_.size(); i++) {
	    obbs_[i]->OnCollision(obbs_[0]->GetOBBMaterial() == obbs_[1]->GetOBBMaterial());
	}*/
	hexagon_->OnCollision(hexagon_->GetHexagonMaterial() == obbs_[0]->GetOBBMaterial());
}
