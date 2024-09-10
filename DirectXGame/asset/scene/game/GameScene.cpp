#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


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
	debugCamera_ = make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
#ifdef _DEBUG
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
#endif // _DEBUG
#pragma endregion

	// クリエイト
	create_ = make_unique<Create>(); // クリエイトクラスの生成
	create_->ModelCreate();          // モデルの生成
	create_->TextureCreate();        // テクスチャの生成

	// レールカメラ
	railCamera_ = make_unique<RailCamera>();                                                                             // 生成
	railCameraWorldTransform_.Initialize();                                                                              // ワールドトランスフォームの初期化
	railCamera_->Initialize(railCameraWorldTransform_.matWorld_, railCameraWorldTransform_.rotation_, &viewProjection_); // 初期化

	// プレイヤー
	player_ = make_unique<Player>(); // 生成
	player_->Initialize(create_.get(), &viewProjection_);
	player_->SetPearent(&railCamera_->GetWorldTransform());
	SetPartisPositionAndAngle(); // パーツの位置をセット

	// インプットハンドラ
	inputHandler_ = make_unique<InputHandler>();
	InputCommand();

	// 天球
	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(create_->GetModel(create_->typeSkyDome), &viewProjection_);
	player_->SetSkyDome(skyDome_.get());

	// フェード
	fieldChangeFade_ = make_unique<Fade>();
	fieldChangeFade_->Initialize();
	fieldChangeFade_->FadeStart(Fade::Status::FadeOut, fadeTime_);

	// スコア
	bitmapFont_ = make_unique<Score>();
	bitmapFont_->Initialize();
	// 敵の表示する場所
	enemyPopCommand_ = make_unique<CSVFailLoading>();
	enemyPopCommand_->Initialize();

	// 敵の親クラス
	enemyParent_ = make_unique<EnemyParent>();
	enemyParent_->Initialize();
	enemyParent_->SetParent(&skyDome_->GetWorldTransform()); // 親を設定

	// プレイヤーのHP
	playerHp_ = make_unique<Hp>();
	playerHp_->Initialize();

	// ワープ
	warp_ = make_unique<Warp>();
	warp_->Initialize(create_->GetModel(create_->typeWarp), &viewProjection_);
	warp_->SetParent(&skyDome_->GetWorldTransform());
}

// 更新
void GameScene::Update() {
	// フィールドの更新
	UpdateField();
#ifdef _DEBUG
	ImGui::Begin("enemyPopCommand");
	for (auto position : enemyPopCommand_->GetPosition()) {
		ImGui::Text("%f,%f,%f", position.x, position.y, position.z);
	}
	for (auto time : enemyPopCommand_->GetPhase()) {
		ImGui::Text("%d", time);
	}
	ImGui::End();
#endif // _DEBUG
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

	// プレイヤー
	player_->Draw();
	if (fieldStatus_ == FieldStatus::kMain) {
		// 障害物
		for (auto* enemy : enemis_) {
			if (enemy) {
				enemy->Draw();
			}
		}
	}
	// 天球
	skyDome_->Draw(isSkyDive_);

	// ワープ
	warp_->Draw();

	// フェードインとフェードアウトに使うスプライト(この下に3Dモデルをおかないで)
	fieldChangeFade_->Draw(commandList);

	railCamera_->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スコアの表示
	bitmapFont_->Draw();
	// プレイヤーのHP
	playerHp_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// 終了フラグのゲッター
bool GameScene::IsFinished() { return isFinished_; }

// 終了フラグのセッター
void GameScene::SetIsFinished(bool isFinished) { isFinished_ = isFinished; }

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

// コマンドを受け取る
void GameScene::InputCommand() {
#pragma region プレイヤーを各方向に移動させる

	inputHandler_->AssignMoveRightCommand2PressKeyD();
	inputHandler_->AssignMoveLeftCommand2PressKeyA();
	inputHandler_->AssignMoveUpCommand2PressKeyW();
	inputHandler_->AssignMoveDownCommand2PressKeyS();

#pragma endregion
}

// コマンドの更新
void GameScene::UpdateCommand() {
	// 横移動
	lateralMovement_ = inputHandler_->HandleInputHorizon();
	if (this->lateralMovement_) {
		lateralMovement_->Exec(*player_);
	}
	// 縦移動
	verticalMvement_ = inputHandler_->HandleInputVertical();
	if (this->verticalMvement_) {
		verticalMvement_->Exec(*player_);
	}
}

// 衝突判定
void GameScene::CheackOnCollision() {
	AABB posA;
	AABB posB;
#pragma region 自キャラと障害物の衝突
	// AABBを受け取る
	posA = player_->GetAABB();

	if (!player_->IsStartFrash()) {

		for (auto* enemy : enemis_) {
			posB = enemy->GetAABB();
			// 衝突判定
			if (Collision::IsCollision(posA, posB)) {
				enemy->OnCollision(); // 衝突したら

				// プレイヤーの残機を一個減らす
				playerHp_->SetHpCount(playerHp_->GetHpCount() - 1);
				player_->OnCollision(playerHp_->GetHpCount());
			}
		}
	}
#pragma endregion
}

// フィールドの更新
void GameScene::UpdateField() {
	// 敵の親クラス
	enemyParent_->Update();
	// 障害物のpopするコマンド
	enemyPopCommand_->Update();
	static int32_t enemyPhaseNum = -1; // 仮の敵の数
	if (!isSetEnemyPos) {
		enemis_.clear(); // 敵を削除
		enemyPhaseNum++; // 敵のフェーズを進めていく
		if (enemyPhaseNum >= (int32_t)enemyPopCommand_->GetPhase().size()) {
			enemyPhaseNum = (int32_t)enemyPopCommand_->GetPhase().size() - 1; // 敵のフェーズがコマンドの数より多いと最大値-1した値を入れる
		}
		for (int i = 0; i < enemyPopCommand_->GetPhase()[enemyPhaseNum]; i++) {
			Enemy* enemy = new Enemy();                                                                                     // 生成
			enemy->Initialize(create_->GetModel(create_->typeEnemy), &viewProjection_, enemyPopCommand_->GetPosition()[i]); // 初期化
			enemy->SetParent(&enemyParent_->GetWorldTransform());                                                           // スカイドームを親にする
			enemis_.push_back(enemy);                                                                                       // 敵を生成する
			isSetEnemyPos = true;                                                                                           // 敵のポジションをセット
		}
	}
	// フェードの時間をスカイドームの進むスピードに合わせる
	if (fadeTime_ > 0.3f) {
		fadeTime_ = kFieldChangeFadeTime - skyDome_->GetVelocityZ() / 10.0f;
	}
	// デバックカメラ
	DebugCameraMove();
	// レールカメラ
	railCamera_->Update();
	// プレイヤー
	player_->Update(skyDome_->GetTranslation().z);
	// スコアの計算
	score_ += skyDome_->GetVelocityZ() / 100.0f * kScoreSource;
	bitmapFont_->SetScore(static_cast<int>(score_)); // スコアの値をセット
	// スコアの表示用の計算
	bitmapFont_->Update();
	// プレイヤーのHPの更新
	playerHp_->Update();
	// 天球
	skyDome_->Update(!fieldChangeFade_->IsFinished());
	// ワープ
	warp_->Update(player_->IsWarpSpawn());
	// フェードを入れた処理
	if (fieldStatus_ == FieldStatus::kFadeIn) {
		fieldChangeFade_->Update(fieldFadeColor_); // 更新
		if (fieldChangeFade_->IsFinished()) {
			fieldStatus_ = FieldStatus::kMain;                             // フェードインが終了したら
			fieldChangeFade_->FadeStart(Fade::Status::FadeOut, fadeTime_); // スタートできるように設定
			// スカイダイブかどうか
			if (isSkyDive_) {
				fieldFadeColor_ = DARK_BROWN; // 色を赤みがかったダークブラウンに設定
			} else {
				fieldFadeColor_ = WHITE; // 白色に設定
			}
		}
	} else if (fieldStatus_ == FieldStatus::kMain) {
		// 障害物
		for (auto* enemy : enemis_) {
			if (enemy) {
				if (enemy) {
					enemy->Update();
				}
			}
		}
		// スカイドームが-1280より上に行ったら
		if (skyDome_->GetWorldPosition().z < -1280.0f) {
			fieldStatus_ = FieldStatus::kFadeOut;
		}
		// 衝突判定
		CheackOnCollision();
		// コマンド
		UpdateCommand();
	} else {
		fieldChangeFade_->Update(fieldFadeColor_); // 更新
		if (fieldChangeFade_->IsFinished()) {
			fieldStatus_ = FieldStatus::kFadeIn;                          // フェードアウトが終了したら
			fieldChangeFade_->FadeStart(Fade::Status::FadeIn, fadeTime_); // スタートできるように設定
			skyDome_->SetTranslation({0.0f, 0.0f, 1252.0f});              // スカイドームの位置をリセット
			player_->SetPosition({0.0f, 0.0f, 50.0f});                    // プレイヤーの位置をリセット
			player_->SetIsShotFirstTime(false);                           // 耳の飛ばしたかのフラグをリセット
			warp_->SetSize(0.0f);                                         // ワープポインタの大きさをリセット
			isSetEnemyPos = false;                                        // 敵の位置を再設定
			// 現在のスカイドームの状態
			if (isSkyDive_) {
				isSkyDive_ = false; // falseを設定
			} else {
				isSkyDive_ = true; // trueに設定
			}
		}
	}
}

// パーツの位置と角度のセッターをまとめた
void GameScene::SetPartisPositionAndAngle() {
	// 位置
	player_->SetPartsPosition(IPlayerParts::head, {-0.81f, 0.69f, 0.00f});   // 頭
	player_->SetPartsPosition(IPlayerParts::body, {1.51f, -1.31f, 0.00f});   // 体
	player_->SetPartsPosition(IPlayerParts::arm, {1.87f, 0.01f, 0.0f});      // 腕
	player_->SetPartsPosition(IPlayerParts::left_arm, {0.0f, 0.0f, 2.5f});   // 左腕
	player_->SetPartsPosition(IPlayerParts::right_arm, {0.0f, 0.0f, -2.5f}); // 右腕
	// 角度
	player_->SetPartsAngle(IPlayerParts::head, {-0.52f, numbers::pi_v<float> / 2.0f, 0.0f}); // 頭
	player_->SetPartsAngle(IPlayerParts::body, {0.0f, 0.0f, 1.01f});                         // 体
	player_->SetPartsAngle(IPlayerParts::arm, {0.0f, 0.0f, 0.0f});                           // 腕
	player_->SetPartsAngle(IPlayerParts::left_arm, {0.3f, -0.91f, 2.7f});                    // 左腕
	player_->SetPartsAngle(IPlayerParts::right_arm, {-0.3f, 0.91f, 2.7f});                   // 右腕
}
