#include "SearchScene.h"



// デストラクタ
SearchScene::~SearchScene() {}

// 初期化
void SearchScene::Initialize() {
	//各オブジェクトの初期化処理
	InitializeObject();
}

// 更新
void SearchScene::Update() {
	// デバックカメラの更新
	DebugCameraMove();
    //地面の更新
	ground_->Update();
	//天球の更新
	skyDome_->Update();
	//自キャラの更新
	player_->Update();
	//敵キャラの更新
	for (auto& enemy : enemies_) {
		enemy->Update();
	}
	// カメラの更新
	followCamera_->Update();
	//ロックオンの更新
	lockOn_->Update(enemies_, viewProjection_);
	//衝突マネージャの更新
	collisionManager_->UpdateWorldTransform();
	//衝突判定と応答
	CheckAllCollision();
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

	// 地面
	ground_->Draw(); 
	// 天球
	skyDome_->Draw(); 
	// 自キャラ
	player_->Draw();
	// 敵
	for (auto& enemy : enemies_) {
		enemy->Draw(); 
	}
	//コライダー
	collisionManager_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//ロックオン
	lockOn_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// モデル生成
void SearchScene::CreateModel() {

	//地面
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	
	//天球
	modelSkydome_.reset(Model::CreateFromOBJ("SkyDome", true));

	//プレイヤーパーツ
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	// 敵モデルデータ
	modelEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelEnemyL_spear_.reset(Model::CreateFromOBJ("spear", true));
	modelEnemyR_spear_.reset(Model::CreateFromOBJ("spear", true));
	// ハンマーの生成
	modelHammer_.reset(Model::CreateFromOBJ("hammer", true));

}

// 各オブジェクトの初期化
void SearchScene::InitializeObject() {

	CreateModel();

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get(), &viewProjection_);

	// 天球の生成
	skyDome_ = std::make_unique<SkyDome>();
	skyDome_->Initialize(modelSkydome_.get(), &viewProjection_);

	// 敵パーツ
	std::vector<Model*> enemyParts = {nullptr, modelEnemyBody_.get(), modelEnemyL_spear_.get(), modelEnemyR_spear_.get()};

	// 敵キャラの生成
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	enemy->Initialize(enemyParts, &viewProjection_);
	enemies_.push_back(std::move(enemy));

	// ロックオンの生成
	lockOn_ = std::make_unique<LockOn>();
	lockOn_->Initialize();

	// 自キャラの生成
	hammer_ = std::make_unique<Hammer>();
	hammer_->Initialize(modelHammer_.get(), &viewProjection_);

    // パーツ
	std::vector<Model*> playerParts = {
	    nullptr,                  // ベース(存在していないのでnullptrにしている)
	    modelFighterBody_.get(),  // 体
	    modelFighterHead_.get(),  // 頭
	    modelFighterL_arm_.get(), // 左腕
	    modelFighterR_arm_.get(), // 右腕
	};

	// プレイヤーの生成
	player_ = std::make_unique<Player>();
	player_->Initialize(playerParts, &viewProjection_);
	player_->SetLockOn(lockOn_.get());
	player_->SetHammer(hammer_.get());
	
	// レールカメラ
	followCamera_->SetTarget(player_->GetWorldTransform()[int(Player::ObjectParts::kBase)]);
	followCamera_->SetLockOn(lockOn_.get());

	//衝突マネージャの生成
	collisionManager_ = std::make_unique<CollisionManager>();
	collisionManager_->Initialize();
}

// 衝突判定と応答
void SearchScene::CheckAllCollision() {
	// 衝突マネージャのリセット
	collisionManager_->Reset();

	// コライダーをリストに登録
	collisionManager_->AddCollider(player_.get());
	// 敵全てについて
	for (const std::unique_ptr<Enemy>& enemy : enemies_) {
		collisionManager_->AddCollider(enemy.get());
	}

	collisionManager_->AddCollider(hammer_.get());

	// 衝突判定と応答
	collisionManager_->CheckAllCollisions();
}