#include "IScene.h"

//終了フラグのゲッター
bool IScene::IsFinished() { return isFinished_; }

//終了フラグ
void IScene::SetIsFinished(bool isFinished) { isFinished_ = isFinished; }

// コンストラクタ
IScene::IScene() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();

#pragma region デバックカメラ
	debugCamera_ = std::make_unique<DebugCamera>(WinApp::kWindowWidth, WinApp::kWindowHeight);
#ifdef _DEBUG
	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
#endif // _DEBUG
#pragma endregion

	// クリエイト
	create_ = Create::GetInstance(); // クリエイトの生成
	create_->ModelCreate();          // モデルの生成
	create_->TextureCreate();        // テクスチャの生成

	// カメラ
	railCamera_ = std::make_unique<RailCamera>();                                                                // レールカメラクラスの生成
	cameraWorldTransform_.Initialize();                                                                          // カメラのワールドトランスフォームの初期化
	railCamera_->Initialize(cameraWorldTransform_.matWorld_, cameraWorldTransform_.rotation_, &viewProjection_); // レールカメラの初期化
}

//デバックカメラの動き
void IScene::DebugCameraMove() {
#ifdef _DEBUG
	debugCamera_->Update(); // デバックカメラの更新
	if (input_->TriggerKey(DIK_UP)&&input_->PushKey(DIK_LSHIFT)) {
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
	if (input_->GetInstance()->TriggerKey(DIK_SPACE)) {
		isFinished_ = true;
	}
}
