#include "BattleScene.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/honeycomb/cell/NormalCell.h"
using namespace std;
// デストラクタ
BattleScene::~BattleScene() {}

// 初期化
void BattleScene::Initialize(Create* create) {
	// 初期化
	IScene::Initialize(create);

	// マップチップ
	mapChipField_ = make_unique<MapChipField>();
	mapChipField_->LoadMapChipCsv("Resources/map/map.csv");

	// スカイドーム
	skydome_ = make_unique<Skydome>();
	skydome_->Initialize(create_->GetModel(create_->typeSkydome), &viewProjection_);

	// 地面(ハニカム)
	ground_ = make_unique<Honeycomb>(mapChipField_.get());
	ground_->Initialize(create_->GetModel(create_->typeHexagon), &viewProjection_);

	// プレイヤー
	player_ = make_unique<Player>();
	player_->Initialize(std::move(create_->GetPlayerModel()), &viewProjection_, create_->GetUiTextureHandle());

	//スペルカード
	spellCardUi_ = make_unique<SpellCardUI>();
	spellCardUi_->Initialize(create_->GetSpellCardModel(), &viewProjection_);
	spellCardUi_->SetParent(&followCamera_->GetWorldTransform());

	// 追従カメラのビュープロジェクションを受け取る
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 追従対象をセット
	//followCamera_->SetTarget(&player_->GetWorldTransform());
	followCamera_->SetTarget(player_.get());

	// リセット(瞬間合わせ)
	followCamera_->Reset();
	// カメラ移動範囲
	followCamera_->SetMovableArea({-30, 400, 0, 50});

	isFollowOn = true; // 追従on

	// コントローラーの生成
	controller_ = Controller::GetInstance();
	controller_->Initialize(player_.get(), followCamera_.get());

	// ミミック
	enemy_ = std::make_unique<Mimic>();
	enemy_->Initialize(std::move(create_->GetMimicModel()), &viewProjection_, create_->GetUiTextureHandle());
	enemy_->SetPlayer(player_.get());

	// スペルカード
	spellCard_ = std::make_unique<SpellCard>();
	spellCard_->Initialize(create_->GetSpellCardModel(), &viewProjection_);

	// 光り輝くパーティクル
	luminous_ = std::make_unique<Luminous>();
	luminous_->Initialize(create_->GetModel(create_->typeParticle), &viewProjection_);
	luminous_->SetDirectionView(&followCamera_->GetViewProjection());

	particle_ = std::make_unique<Particle>();
	particle_->Initialize(create_->GetModel(create_->typeParticle), &viewProjection_);
	particle_->SetParent(&luminous_->GetCenter());
	particle_->SetDirectionView(&followCamera_->GetViewProjection());

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
	serchlight_->Update();

	ImGui::Begin("wireFrame");
	/*serchlight_->DebugText();*/
	ImGui::End();
#endif // _DEBUG

	// 環境の更新
	skydome_->Update();
	ground_->Update();

	// コントローラのタイプ
	controller_->ControlUpdate((Controller::ControlType)isSelectContorol_);

	// プレイヤーの更新
	player_->Update();
	player_->DebugText("player");

	// カメラの更新
	followCamera_->Update();

	// 敵の更新
	enemy_->Update();

	// スペルカードの更新
	spellCard_->Update();
	spellCardUi_->Update();

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

	// プレイヤーの描画
	player_->Draw();

	// 敵の描画
	enemy_->Draw();

	// スペルカードの描画
	spellCard_->Draw(create_->GetTextureHandle()[create_->typeThunder]);
	spellCardUi_->Draw(create_->GetTextureHandle()[create_->typeFire]);

	// luminous_->Draw();
	// particle_->Draw();

	// 環境の描画
	skydome_->Draw();
	ground_->Draw();

#pragma region ワイヤーフレームの表示

	ground_->DrawWire();
	player_->DrawWire();
	spellCard_->DrawWire();
	// serchlight_->Draw();
#pragma endregion
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	player_->DrawSprite();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// 当たり判定を計算
void BattleScene::CheckCollision() {
	for (auto row : ground_->GetWireFrame()) {
		for (auto cell : row) {
			if (cell) {
				if (cell->GetWireFrame()->GetHexagonMaterial() == player_->GetWireFrame()->GetOBBMaterial()) {
					cell->OnCollision(cell->GetWireFrame()->GetHexagonMaterial() == player_->GetWireFrame()->GetOBBMaterial());
					break;
				} else {
					cell->GetWireFrame()->SetIsHit(false);
				}
			}
		}
	}

	spellCard_->GetWireFrame()->OnCollision(player_->GetWireFrame()->GetOBBMaterial() == spellCard_->GetWireFrame()->GetOBBMaterial());
	if (player_->GetWireFrame()->GetOBBMaterial() == spellCard_->GetWireFrame()->GetOBBMaterial()) {
		spellCard_->OnCollision();
	}
}
