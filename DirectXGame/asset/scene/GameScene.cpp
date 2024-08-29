#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "asset/math/Math.h"
#include <cassert>

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {}

// 初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	// ゲームシーン
	viewProjection_.Initialize();
	// クリエイトクラス
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成
	create_->TextureCreate();        // テクスチャを生成

	// レールカメラ
	railCameraWorldTransform_.Initialize();
	railCamera_ = make_unique<RailCamera>();                                                           // 生成
	railCamera_->Initialize(railCameraWorldTransform_.matWorld_, railCameraWorldTransform_.rotation_); // 初期化

	// プレイヤークラス
	Create::ObjectType typePlayer = Create::Type::kPlayer;
	player_ = make_unique<Player>(); // 生成
	Vector3 playerPosition = {0.0f, -8.0f, 25.0f};
	player_->Initialize(create_->GetModel(typePlayer), &viewProjection_, create_->GetTextureHandle(typePlayer), playerPosition); // 初期化
	player_->SetParent(&railCamera_->GetWorldTransform());                                                                       // 自キャラとレールカメラの親子関係を結ぶ
	// キー入力のコマンドの初期化
	InputCommandInitialize();

	// 敵のクラス
	Create::ObjectType typeEnemy = Create::Type::kEnemy;
	enemy_ = make_unique<Enemy>();                                                                                          // 生成
	enemy_->Initialize(create_->GetModel(typeEnemy), &viewProjection_, create_->GetTextureHandle(typeEnemy), {30, 3, 100}); // 初期化
	enemy_->SetPlayer(player_.get());                                                                                       // プレイヤーをセット

	// スカイドームクラス
	Create::ObjectType typeSkydome = Create::Type::kSkydome;
	skydome_ = make_unique<Skydome>();                                      // 生成
	skydome_->Initialize(create_->GetModel(typeSkydome), &viewProjection_); // 初期化

	contorolPoints_ = {
	    {0,  0,  0},
        {10, 10, 0},
        {10, 15, 0},
        {20, 15, 0},
        {20, 0,  0},
        {30, 0,  0},
	};

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

	// レールカメラ
	railCamera_->Update(); // 更新

	// プレイヤー
	player_->Update();                                            // 更新
	PlayerActionCommand();                                        // 移動のコマンド
	railCamera_->SetRotation(player_->GetParentRotation());       // 角度をセット
	railCamera_->SetTranslation(player_->GetParentTranslation()); // 座標をセット

	// 敵
	enemy_->Update();

	// スカイドーム
	skydome_->Update();

	// デバックカメラ
	debugCamera_->Update(); // 更新
	DebugCameraMove();      // デバックカメラの動き

	// 衝突しているかどうか
	CheckAllCollision();
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

	// 敵
	if (enemy_) {
		enemy_->Draw();
	}

	// スカイドーム
	skydome_->Draw();

	// 曲線で描画する用の頂点リスト
	vector<Vector3> pointsDrawing;
	// 線分の数
	const size_t segmentCount = 100;
	// 線分の数+1個分の頂点座標を計算
	for (size_t i = 0; i < segmentCount + 1; i++) {
		float t = 1.0f / segmentCount * i;
		Vector3 pos = Math::CatmullRomPosition(contorolPoints_, t);
		// 描画用語頂点リストに追加
		pointsDrawing.push_back(pos);
	}

	// 描画
	for (size_t i = 0; i < segmentCount; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing[i], pointsDrawing[i + 1], {1.0f, 0.0f, 0.0f, 1.0f});
	}

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
	const list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const list<EnemyBullet*>& enemyBullets = enemy_->GetBullet();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラ
	posA = player_->GetAABB();
	for (auto enemyBullet : enemyBullets) {
		// 敵弾
		posB = enemyBullet->GetAABB();
		if (Collision::IsCollision(posA, posB)) {
			// 自キャラの衝突時のコールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時のコールバックを呼び出す
			enemyBullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラ
	posB = enemy_->GetAABB();
	for (auto playerBullet : playerBullets) {
		if (playerBullet) {
			// 自弾
			posA = playerBullet->GetAABB();
			if (Collision::IsCollision(posA, posB)) {
				// 自弾の衝突時のコールバックを呼び出す
				playerBullet->OnCollision();
				// 敵キャラの衝突時のコールバックを呼び出す
				enemy_->OnCollision();
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
