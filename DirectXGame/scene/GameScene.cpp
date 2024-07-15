#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "calculate/Math.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelBlock_; // Blockの3Dモデルの削除

	// 拡張for文
	for (std::vector<WorldTransform*>& worldTransformBlockLine :
	     blocks_->GetBlocks()) { //&を付けることで値を参照して使えるようにしている(&を付けないと値がコピーされたものしか取り出せなくなるのでオリジナルをdeleteできない)
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock; // 配列の中身を削除
		}
	}
	blocks_->GetBlocks().clear(); // 配列の箱自体を削除

	delete debugCamera_; // デバックカメラの削除

	delete skydome_;      // スカイドームの削除
	delete skydomeModel_; // スカイドームモデルの削除

	delete player_;      // プレイヤーの削除
	delete playerModel_; // プレイヤーのモデルの削除

	delete mapChipField_; // マップチップの削除

	for (Enemy* enemy : enemies_) {
		delete enemy; // エネミー
	}
	enemies_.clear();

	delete deathParticles_; // 死んだときのパーティクルの削除
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight); // デバックカメラの生成
	debugCamera_->SetFarZ(2000);                                                 // farClipの変更

	mapChipField_ = new MapChipField();                     // マップチップの生成
	mapChipField_->LoadMapChipCsv("Resources/map/map.csv"); // マップチップの読み込み
	GenerateBlocks();                                       // ブロックの生成

	skydome_ = new Skydome;                                // スカイドームの生成
	skydomeModel_ = Model::CreateFromOBJ("skydome", true); // モデルの読み込み(obj)
	skydome_->Initialize(skydomeModel_, &viewProjection_); // スカイドームの初期化

	playerModel_ = Model::CreateFromOBJ("player", true);                                             // プレイヤーのモデルの生成
	playerTextureHandle_ = TextureManager::Load("cube/cube.jpg");                                    // プレイヤーのテクスチャ
	Vector3Int playerIndex = {1, 13};                                                                // プレイヤーのいる場所の検索
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(playerIndex.x, playerIndex.y); // プレイヤーのいるポジション
	player_ = new Player;                                                                            // プレイヤークラスの生成
	player_->Initialize(playerModel_, playerTextureHandle_, &viewProjection_, playerPosition);       // プレイヤーの初期化
	player_->SetMapChipField(mapChipField_);

	enemyModel_ = Model::CreateFromOBJ("player", true);          // エネミーのモデルの生成
	enemyTextureHandle_ = TextureManager::Load("uvChecker.png"); // エネミーのテクスチャの読み込み
	for (int i = 0; i < kEnemyNum; ++i) {
		Enemy* newEnemy = new Enemy();                                                                // エネミーの生成
		Vector3Int enemyIndex = {20 + 1 * i, 18};                                                     // エネミーのいる場所の検索
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(enemyIndex.x, enemyIndex.y); // エネミーのいるポジション
		newEnemy->Initialize(enemyModel_, enemyTextureHandle_, &viewProjection_, enemyPosition);      // エネミーの初期化
		newEnemy->SetMapChipField(mapChipField_);                                                     // マップチップフィールドをセット
		enemies_.push_back(newEnemy);                                                                 // 値の追加
	}

	cameraController_ = new CameraController();           // カメラコントロールの生成
	cameraController_->Initialize();                      // カメラコントロールの初期化
	cameraController_->SetTarget(player_);                // ターゲットのセット
	cameraController_->Reset();                           // リセット
	cameraController_->SetMovableArea({20, 175, 10, 20}); // カメラの追従範囲

	deathParticles_ = new DeathParticles();                                                                // 死んだときのパーティクルの生成
	particleModel_ = Model::CreateFromOBJ("particle", true);                                               // パーティクルモデルの生成
	particleTextureHandle_ = TextureManager::Load("white1x1.png");                                         // テクスチャのロード
	deathParticles_->Initialize(particleModel_, &viewProjection_, playerPosition, particleTextureHandle_); // 死んだときのパーティクルの初期化

	phase_ = Phase::kPlay; // プレイヤーの状態
	isDeath_ = false;      // デスフラグ
	finished_ = false;     // 終了フラグ
	fade_ = new Fade();
	fade_->Initialize();
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTime);
}

void GameScene::Update() {

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_BACK)) {
		isDebugCameraActive_ ^= true;
	}
#endif
	// フェーズ
	ChangeFadePhaseUpdate();
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

	// フェーズ
	ChangePhaseDraw();

	fade_->Draw(commandList);

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

// ブロックを出す初期化処理をまとめた
void GameScene::GenerateBlocks() {
	modelBlock_ = Model::Create();                            // ブロックのモデル生成
	blockTextureHandle_ = TextureManager::Load("kamata.ico"); // ブロックのテクスチャ
	viewProjection_.Initialize();                             // ブロックの初期化
	// viewProjection_.farZ = 2000;
	blocks_ = new Blocks;                                                                   // ブロックの生成
	blocks_->Initialize(modelBlock_, blockTextureHandle_, &viewProjection_, mapChipField_); // ブロックの初期化
}

// カメラの更新
void GameScene::CameraUpdate() {
	// カメラの処理
	if (isDebugCameraActive_) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = cameraController_->GetViewProjection().matView;
		viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	}
}

// 敵とプレイヤーが当たっているかどうかの関数
void GameScene::CheckAllCollision() {
#pragma region 自キャラと敵キャラの当たり判定
	// 自キャラと敵キャラの当たり判定
	AABB aabb1, aabb2;
	aabb1 = player_->GetAABB();
	// 複数の敵の当たり判定
	for (Enemy* enemy : enemies_) {
		aabb2 = enemy->GetAABB();
		if (IsHit(aabb1, aabb2)) {
			isDeath_ = player_->OnCollision(enemy);
			enemy->OnCollision(player_);
		}
	}
#pragma endregion
}

void GameScene::ChangePhaseUpdate() {
	blocks_->Update(); // ブロック
	// カメラの更新
	CameraUpdate();
	switch (phase_) {

	case Phase::kPlay:

		debugCamera_->Update();      // デバックカメラ
		cameraController_->Update(); // 追従カメラ

		for (Enemy* enemy : enemies_) {
			enemy->Update(fade_->IsFinished()); // エネミー
		}

		player_->Update(fade_->IsFinished()); // プレイヤー
		CheckAllCollision();
		if (isDeath_) {
			phase_ = Phase::kDeath; // 死亡演出に切り替え
			// 自キャラの座標を取得
			const Vector3& deathParticlePosition = player_->GetWorldPosition();
			// 自キャラの座標にデスパーティクルを発生
			deathParticles_->SetPosition(deathParticlePosition);
		}

		break;

	case Phase::kDeath:
		// for (Enemy* enemy : enemies_) {
		//	enemy->Update(); // エネミー
		// }
		if (deathParticles_ != nullptr&&!deathParticles_->IsFinished()) {
			deathParticles_->Update(); // パーティクル
		}
	
		// デスパーティクルが出きった時に終了するフラグ
		if (deathParticles_->IsFinished()) {
			fadePhase_ = FadePhase::kFadeOut;
			if (isFadeIni) {
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
			}
			isFadeIni = false;
			deathParticles_->SetIsFinished(false);
		}
		break;
	}
}

// フェードを入れたフェーズの変更
void GameScene::ChangeFadePhaseUpdate() {
	switch (fadePhase_) {
	case FadePhase::kFadeIn:
		// フェードイン
		fade_->Update();
		ChangePhaseUpdate();
		if (fade_->IsFinished()) {
			fadePhase_ = FadePhase::kMain;
		}
		break;
	case FadePhase::kMain:
		// メイン部
		ChangePhaseUpdate();
		break;
	case FadePhase::kFadeOut:
		// フェードアウト
		fade_->Update();
		ChangePhaseUpdate();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
}

// フェーズの変更
void GameScene::ChangePhaseDraw() {

	skydome_->Draw(); // スカイドーム

	blocks_->Draw(); // ブロック

	for (Enemy* enemy : enemies_) {
		enemy->Draw(); // エネミー
	}

	switch (phase_) {

	case Phase::kPlay:

		player_->Draw(); // プレイヤー

		break;

	case Phase::kDeath:

		deathParticles_->Draw(); // パーティクル

		break;
	}
}

// デスフラグのゲッター
bool GameScene::IsDeath() const { return isDeath_; }

// 終了フラグのゲッター
bool GameScene::IsFinished() const { return finished_; }

// 終了フラグのセッター
void GameScene::SetIsFinished(const bool& isFinished) { finished_ = isFinished; }
