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

	// インプットハンドラ
	inputHandler_ = make_unique<InputHandler>();
	InputCommand();

	// 障害物
	enemy_ = make_unique<Enemy>();
	Vector3 enemyPos = {0, 0, 50.0f};
	enemy_->Initialize(create_->GetModel(create_->typeEnemy), &viewProjection_, enemyPos);

	// 天球
	skyDome_ = make_unique<SkyDome>();
	skyDome_->Initialize(create_->GetModel(create_->typeSkyDome), &viewProjection_);

	// フェード
	fieldChangeFade_ = make_unique<Fade>();
	fieldChangeFade_->Initialize();
	fieldChangeFade_->FadeStart(Fade::Status::FadeOut, kFieldChangeFadeTime);
}

// 更新
void GameScene::Update() {
	// フィールドの更新
	UpdateField();
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
		enemy_->Draw();
	}
	// 天球
	skyDome_->Draw();

	// フェードインとフェードアウトに使うスプライト
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

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

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
	posB = enemy_->GetAABB();
	// 衝突判定
	if (Collision::IsCollision(posA, posB)) {
		enemy_->OnCollision(); // 衝突したら
	}
#pragma endregion
}

// フィールドの更新
void GameScene::UpdateField() {
	// デバックカメラ
	DebugCameraMove();
	// レールカメラ
	railCamera_->Update();
	// プレイヤー
	player_->Update();
	// 天球
	skyDome_->Update(!fieldChangeFade_->IsFinished());

	//フェードを入れた処理
	if (fieldStatus_ == FieldStatus::kFadeIn) {
		fieldChangeFade_->Update(fieldFadeColor_); // 更新
		if (fieldChangeFade_->IsFinished()) {
			fieldStatus_ = FieldStatus::kMain;//フェードインが終了したら
			fieldChangeFade_->FadeStart(Fade::Status::FadeOut, kFieldChangeFadeTime);//スタートできるように設定
			//スカイダイブかどうか
			if (isSkyDive_) {
				isSkyDive_ = false;//falseを設定
				fieldFadeColor_ = BLACK;//色を黒色に設定
			} else {
				isSkyDive_ = true;//trueに設定
				fieldFadeColor_ = WHITE;//白色に設定
			}
		}
	} else if (fieldStatus_ == FieldStatus::kMain) {
		//スカイドームが-1280より上に行ったら
		if (skyDome_->GetWorldTransform().z < -1280.0f) {
			fieldStatus_ = FieldStatus::kFadeOut;
		}
		// 衝突判定
		CheackOnCollision();
		// コマンド
		UpdateCommand();
		// 障害物
		enemy_->Update();
	} else {
		fieldChangeFade_->Update(fieldFadeColor_);//更新
		if (fieldChangeFade_->IsFinished()) {
			fieldStatus_ = FieldStatus::kFadeIn;//フェードアウトが終了したら
			fieldChangeFade_->FadeStart(Fade::Status::FadeIn, kFieldChangeFadeTime);//スタートできるように設定
			skyDome_->SetTranslation({0.0f, 0.0f, 1252.0f});//スカイドームの位置をリセット
			player_->SetTranslation({0.0f, 0.0f, 50.0f});//プレイヤーの位置をリセット
		}
	}
}
