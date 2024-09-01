#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include "WinApp.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <ctime>

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	for (auto enemyBullet : enemyBullets_) {
		delete enemyBullet; // 弾を削除
	}
	enemyBullets_.clear(); // 弾のあった配列も削除

	for (auto playerBullet : playerBullets_) {
		delete playerBullet; // 弾を削除
	}
	playerBullets_.clear(); // 弾のあった配列も削除

	for (auto enemy : enemies_) {
		delete enemy; // 敵を削除
	}
	enemies_.clear(); // 敵の配列を削除
	delete enemy_;    // 敵単体を消す
}

// 初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	srand(static_cast<unsigned int>(time(nullptr)));
	// ゲームシーン
	viewProjection_.Initialize();
	// クリエイトクラス
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成
	create_->TextureCreate();        // テクスチャを生成

	// レールカメラ
	railCameraWorldTransform_.Initialize();
	railCamera_ = make_unique<RailCamera>();                                                                             // 生成
	railCamera_->Initialize(railCameraWorldTransform_.matWorld_, railCameraWorldTransform_.rotation_, &viewProjection_); // 初期化

	// プレイヤークラス
	Create::ObjectType typePlayer = Create::Type::kPlayer;
	player_ = make_unique<Player>(); // 生成
	Vector3 playerPosition = {0.0f, -2.0f, 22.0f};
	player_->Initialize(create_->GetModel(typePlayer), &viewProjection_,playerPosition); // 初期化
	player_->SetParent(&railCamera_->GetWorldTransform());                                                                       // 自キャラとレールカメラの親子関係を結ぶ
	player_->SetGameScene(this);                                                                                                 // ゲームシーンをセット
	// キー入力のコマンドの初期化
	InputCommandInitialize();

	// 敵のクラス
	//LoadEnemyPopDate();
	 Create::ObjectType typeEnemy = Create::Type::kEnemy;
	 for (int i = 0; i < kEnemyNum; i++) {
		 Enemy* enemy = new Enemy();                                                                                             // 生成
		 float multiple = static_cast<float>(rand() % 6 - 3);
		 enemy->Initialize(create_->GetModel(typeEnemy), &viewProjection_, {30.0f * multiple, 3 * multiple, 100}); // 初期化
		enemy->SetGameScene(this);                                                                                                        // ゲームシーンをセット
		enemy->SetPlayer(player_.get());                                                                                                  // プレイヤーをセット
		enemies_.push_back(enemy);                                                                                                        // 敵を登録
	 }

	// スカイドームクラス
	Create::ObjectType typeSkydome = Create::Type::kSkydome;
	skydome_ = make_unique<Skydome>();                                      // 生成
	skydome_->Initialize(create_->GetModel(typeSkydome), &viewProjection_); // 初期化

	//地面
	Create::ObjectType typeGround = Create::Type::kGround;
	ground_ = make_unique<Ground>();//生成
	ground_->Initialise(create_->GetModel(typeGround), &viewProjection_);//初期化

	//フェード
	fade_=make_unique<Fade>();
	fade_->Initialize();
	fade_->FadeStart(Fade::Status::FadeIn,kFadeTime);

	//デスパーティクル
	Create::ObjectType typeParticle = Create::Type::kParticle;
	playerDethParticle_ = make_unique<DeathParticles>();
	playerDethParticle_->Initialize(create_->GetModel(typeParticle), &viewProjection_, playerPosition);


#pragma region デバックカメラ
	debugCamera_ = make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
#ifdef _DEBUG
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
#endif // _DEBUG
#pragma endregion
}

// 更新
void GameScene::Update() { 
	//更新処理をまとめた
	ChangeUpdate(); 
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

	ChangeDraw();//ゲームシーンの描画処理をまとめた
	fade_->Draw(commandList);//フェードの画像


	// カメラの軌道
	// railCamera_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	//レティクル
	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// 終了フラグのゲッター
bool GameScene::IsFinished() const { return isFinished_; }

// 終了フラグのセッター
void GameScene::SetIsFinished(const bool& isFinished) { isFinished_ = isFinished; }

// キー入力のコマンドの初期化
void GameScene::InputCommandInitialize() {
	inputHandle_ = make_unique<InputHandle>();
	inputHandle_->Initialize(input_);
	inputHandle_->AssingMoveLeftCommand2PressKeysLeft();   // 左へ
	inputHandle_->AssingMoveRightCommand2PressKeysRight(); // 右へ
	inputHandle_->AssingMoveDownCommand2PressKeysDown();   // 下へ
	inputHandle_->AssingMoveUpCommand2PressKeysUp();       // 上へ
	inputHandle_->AssingRotateLeftCommand2PressKeyA();     // 左回転
	inputHandle_->AssingRotateRightCommand2PressKeyD();    // 右回転
}

// プレイヤーのコマンドをまとめた
void GameScene::PlayerActionCommand() {
	// 移動
	player_->SetVelocity({});                                          // 速度の初期化
	iPlayerCommandBeside_ = inputHandle_->PlayerBesideMoveInput();     // 横移動
	iPlayerCommandVertical_ = inputHandle_->PlayerVerticalMoveInput(); // 縦移動
	if (iPlayerCommandBeside_) {
		iPlayerCommandBeside_->Exec(*player_); // 横移動
	}
	if (iPlayerCommandVertical_) {
		iPlayerCommandVertical_->Exec(*player_); // 縦移動
	}

	// 旋回
	iPlayerCommandRotate_ = inputHandle_->PlayerRotateInput(); // 旋回
	if (iPlayerCommandRotate_) {
		iPlayerCommandRotate_->Exec(*player_); // 旋回
	}
}

// デバックカメラ
void GameScene::DebugCameraMove() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_BACKSPACE)) {
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

// 衝突判定の応答
void GameScene::CheckAllCollision() {

	// 判定対象AとBの座標
	AABB posA, posB;
	// 自弾リストの取得
	const list<PlayerBullet*>& playerBullets = playerBullets_;
	// 敵弾リストの取得
	const list<EnemyBullet*>& enemyBullets = enemyBullets_;

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラ
	posA = player_->GetAABB();
	for (auto enemyBullet : enemyBullets) {
		// 敵弾
		posB = enemyBullet->GetAABB();
		if (Collision::IsCollision(posA, posB)) {
			// 自キャラの衝突時のコールバックを呼び出す
			player_->OnCollision();
			playerStatus_ = Status::kDeth;
			// 敵弾の衝突時のコールバックを呼び出す
			enemyBullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	for (auto playerBullet : playerBullets) {
		for (auto enemy : enemies_) {
			if (playerBullet) {
				// 自弾
				posA = playerBullet->GetAABB();
				// 敵キャラ
				posB = enemy->GetAABB();
				if (Collision::IsCollision(posA, posB)) {
					// 自弾の衝突時のコールバックを呼び出す
					playerBullet->OnCollision();
					// 敵キャラの衝突時のコールバックを呼び出す
					enemy->OnCollision(killNum);
					
				}
			}
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (auto playerBullet : playerBullets) {
		if (playerBullet) {
			for (auto enemyBullet : enemyBullets) {

				// 自弾
				posA = playerBullet->GetAABB();
				// 敵弾
				posB = enemyBullet->GetAABB();
				if (Collision::IsCollision(posA, posB)) {
					// 自弾の衝突時のコールバックを呼び出す
					playerBullet->OnCollision();
					// 敵弾の衝突時のコールバックを呼び出す
					enemyBullet->OnCollision();
				}
			}
		}
	}
#pragma endregion
}

// 敵発生データの読み込み
void GameScene::LoadEnemyPopDate() {
	// ファイルを開く
	ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());
	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

// 敵発生コマンドの更新
void GameScene::UpdateEnemyPopCommands() {
	// 待機処理
	if (isEnemyWaite_) {
		enemyWaitTime_--;
		if (enemyWaitTime_ <= 0) {
			// 待機完了
			enemies_.push_back(enemy_); // 敵を生成
			isEnemyWaite_ = false;
		}
		return;
	}
	Create::ObjectType typeEnemy = Create::Type::kEnemy; // モデルの配列番号
	// 1行分の文字列を入れる変数
	string line;
	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		if (line.empty()) {
			continue; // 空行を飛ばす
		}
		// 1行分の文字列をストリームに変換して解析しやすくする
		istringstream line_stream(line); // 読み込んだ行を文字列ストリームに変換
		string word;                     // 行から切り出した単語を格納する変数

		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)atof(word.c_str());
			// 敵を発生させる
			enemy_ = new Enemy();
			enemy_->Initialize(create_->GetModel(typeEnemy), &viewProjection_, Vector3(x, y, z));
			enemy_->SetGameScene(this);
			enemy_->SetPlayer(player_.get());
		} else if (word.find("WHITE") == 0) {
			getline(line_stream, word, ',');
			// 待ち時間
			int32_t waitTime = atoi(word.c_str());
			// 待機開始
			isEnemyWaite_ = true;
			enemyWaitTime_ = waitTime;
			// コマンドループを抜ける
			break;
		}
	}
}

//更新のフェーズ
void GameScene::ChangeUpdate() {
	// レールカメラ
	railCamera_->Update(); // 更新
	// プレイヤー
	player_->Update();     // 更新

	// スカイドーム
	skydome_->Update();

	// 地面
	ground_->Update();

	// デバックカメラ
	debugCamera_->Update(); // 更新
	DebugCameraMove();      // デバックカメラの動き


	switch (phase_) { 
	case Phase::kFadeIn:
		fade_->Update();//フェードイン
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;//フェードインが終わったら
		}
		break;
	case Phase::kMain:

		// デスフラグの立った自弾を削除
		playerBullets_.remove_if([](PlayerBullet* bullet) {
			if (bullet) {
				if (bullet->IsDead()) {
					delete bullet;
					bullet = nullptr;
					return true;
				}
			}
			return false;
		});

		// 自弾
		for (auto playerBullet : playerBullets_) {
			if (playerBullet) {
				playerBullet->Update();
			}
		}

		fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);//フェードの初期化
		if (killNum == 3) {
			phase_ = Phase::kFadeOut;
		}
		switch (playerStatus_) { 
		case Status::kPlay:
			// デスフラグが立ったとき敵を削除
			enemies_.remove_if([](Enemy* enemy) {
				if (enemy) {
					if (enemy->IsDead()) {
						delete enemy;
						return true;
					}
				}
				return false;
			});

			// 敵
			//UpdateEnemyPopCommands(); // 敵を出現
			for (auto enemy : enemies_) {
				if (enemy) {
					enemy->Update(); // 敵の更新
				}
			}

			// 敵弾
			//  デスフラグが立った敵弾を削除
			enemyBullets_.remove_if([](EnemyBullet* bullet) {
				if (bullet) {
					if (bullet->IsDead()) {
						delete bullet;
						return true;
					}
				}
				return false;
			});

			// 敵弾
			for (auto enemyBullet : enemyBullets_) {
				if (enemyBullet) {
					enemyBullet->SetPlayer(player_.get());
					enemyBullet->Update();
				}
			}


			// 衝突しているかどうか
			CheckAllCollision();
			break;
		case Status::kDeth:
			playerDethParticle_->Update();//デスパーティクルの更新
			if (playerDethParticle_->IsFinished()) {
				phase_ = Phase::kFadeOut;
			}
			break;
		}
		PlayerActionCommand(); // 移動のコマンド

		
#ifdef _DEBUG
		//if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		//	phase_ = Phase::kFadeOut;//スペースを押したらフェードアウトを起動できるようにしている
		//}
#endif // _DEBUG

		break;
	case Phase::kFadeOut:
		fade_->Update();//フェードの更新
		if (fade_->IsFinished()) {
			isFinished_ = true;//ゲームシーンを終了する
		}
		break;
	}
}

//描画のフェーズ
void GameScene::ChangeDraw() {

	// 自弾
	for (auto playerBullet : playerBullets_) {
		if (playerBullet) {
			playerBullet->Draw(viewProjection_);
		}
	}

	// スカイドーム
	skydome_->Draw();

	// 地面
	ground_->Draw();

	switch (phase_) { 
	case Phase::kFadeIn:
		// プレイヤー
		player_->Draw();
		break;
	case Phase::kMain:
		switch (playerStatus_) { 
		case Status::kPlay:
			// プレイヤー
			player_->Draw();
			playerDethParticle_->SetPosition(player_->GetWorldPosition());
			break;
		case Status::kDeth:
			playerDethParticle_->Draw();
			break;
		}
		// 敵
		for (auto enemy : enemies_) {
			if (enemy) {
				enemy->Draw();
			}
		}

		// 敵弾
		for (auto enemyBullet : enemyBullets_) {
			if (enemyBullet) {
				enemyBullet->Draw(viewProjection_);
			}
		}
		break;
	case Phase::kFadeOut:
		switch (playerStatus_) { 
		case Status::kPlay:
			player_->Draw();
			break;
		}
		// 敵
		for (auto enemy : enemies_) {
			if (enemy) {
				enemy->Draw();
			}
		}

		// 敵弾
		for (auto enemyBullet : enemyBullets_) {
			if (enemyBullet) {
				enemyBullet->Draw(viewProjection_);
			}
		}
		break;
	}

}

// 敵弾を追加する
void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}

// 敵弾モデルのゲッター
Model* GameScene::GetEnemyBulletModel() const {
	Create::ObjectType typeEnemyBullet = Create::Type::kEnemyBullet;
	return create_->GetModel(typeEnemyBullet);
}

// 自弾を追加する
void GameScene::AddPlayerBullet(PlayerBullet* playerBullet) {
	// リストに追加
	playerBullets_.push_back(playerBullet);
}
// 自弾モデルのゲッター
Model* GameScene::GetPlayerBulletModel() const {
	Create::ObjectType typePlayerBullet = Create::Type::kPlayerBullet;
	return create_->GetModel(typePlayerBullet);
}
