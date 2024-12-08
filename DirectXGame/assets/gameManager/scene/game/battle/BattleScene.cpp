#include "BattleScene.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/honeycomb/Honeycomb.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/skydome/Skydome.h"
using namespace std;
// デストラクタ
BattleScene::~BattleScene() {}

// 初期化
void BattleScene::Initialize() {
	// OBB
	obb_ = make_unique<OBB>(); // 生成
	obbMaterial_ = {
	    .center{0.0f, 0.0f, 0.0f},
	};
	obb_->Initialize(&viewProjection_, move(obbMaterial_)); // 初期化

	// 六角形
	hexagon_ = make_unique<Hexagon>();
	hexagonMatrial_ = {
	    .center{},
	};
	hexagon_->Initialize(&viewProjection_, move(hexagonMatrial_));

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
	//体力
	playerLifeBar_ = std::make_unique<LifeBar>(player_->GetCharacterType());
	playerLifeBar_->Initialize(create_->GetTextureHandle());

	// 追従カメラのビュープロジェクションを受け取る
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// 追従対象をセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	isFollowOn = true; // 追従on

	// コントローラーの生成
	controller_ = Controller::GetInstance();
	controller_->Initialize(player_.get(), followCamera_.get());

	// ミミック
	enemy_ = std::make_unique<Mimic>();
	enemy_->Initialize(std::move(create_->GetMimicModel()), &viewProjection_);
	enemy_->SetPlayer(player_.get());
	enemyLifeBar_ = std::make_unique<LifeBar>(enemy_->GetCharacterType());
	enemyLifeBar_->Initialize(create_->GetTextureHandle());


	// 光り輝くパーティクル
	luminous_ = std::make_unique<Luminous>();
	luminous_->Initialize(create_->GetModel(create_->typeParticle), &viewProjection_);
	luminous_->SetDirectionView(&followCamera_->GetViewProjection());

	particle_ = std::make_unique<Particle>();
	particle_->Initialize(create_->GetModel(create_->typeParticle), &viewProjection_);
}

// 更新
void BattleScene::Update() {
	//ループをさせる処理
	if (isDead_ || isClear_) {
		isDead_ = false;
		isClear_ = false;
		Initialize();
	}
	// デバックカメラの更新
	DebugCameraMove();

	// カメラの更新
	railCamera_->Update();
#ifdef _DEBUG
	// 六角形
	hexagon_->Update();
	hexagon_->DebugText();

	// OBB
	obb_->Update();
	obb_->DebagText();
#endif // _DEBUG

	// 環境の更新
	for (auto& evbiroment : environments_) {
		evbiroment->Update();
	}

	// コントローラのタイプ
	controller_->ControlUpdate((Controller::ControlType)isSelectContorol_);
	//キーボードで操作を切り替え処理
	if (!isSelectContorol_) {
		if (Input::GetInstance()->PushKey(DIK_0)) {
			isSelectContorol_ = true;
		}
	}
	else {
		if (Input::GetInstance()->PushKey(DIK_0)) {
			isSelectContorol_ = false;
		}
	}

	// プレイヤーの更新
	player_->Update();

	//playerLifeBar_->DebugWindow();
	isDead_ = playerLifeBar_->Update();

	// カメラの更新
	followCamera_->Update();

	// 敵の更新
	enemy_->Update();
	isClear_ = enemyLifeBar_->Update();

	//luminous_->Update();
	//luminous_->DebugText();
	//particle_->Update();
	//particle_->DebugText();

	//当たり判定チェック
	CheckPlayerEnemyCollision();
	//武器の当たり判定
	CheckPlayerAttack();
#ifdef _DEBUG
	// デバック
	ImGui::Begin("test");
	ImGui::Checkbox("controlType", &isSelectContorol_);

	player_->DebugText("player");

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

	// OBB
	// obb_->Draw();
	// hexagon_->Draw();

	// 環境の描画
	for (auto& evbiroment : environments_) {
		evbiroment->Draw();
	}
	// プレイヤーの描画
	player_->Draw();

	// 敵の描画
	enemy_->Draw();

	//luminous_->Draw();
	//particle_->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	playerLifeBar_->Draw();
	enemyLifeBar_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void BattleScene::CheckPlayerEnemyCollision(){
	bool isCollision = false;
	AABB player, enemy;
	player = player_->GetAABB();
	enemy = enemy_->GetAABB();

	isCollision = Collision::GetInstance()->IsCollision(player, enemy);
	if (isCollision) {
		playerLifeBar_->TookDamage();
	}
	else {
		isCollision = false;
	}
}

void BattleScene::CheckPlayerAttack(){
	bool isCollision = false;
	AABB playerWeapon, enemy;

	playerWeapon = player_->GetPartsAABB(PlayerModel::Parts::kStaff);
	enemy = enemy_->GetAABB();

	isCollision = Collision::GetInstance()->IsCollision(playerWeapon, enemy);
	if (isCollision && player_->GetBehavior()== PlayerMode::kBlow) {
		enemyLifeBar_->TookDamage();
	}
	else {
		isCollision = false;
	}
}
