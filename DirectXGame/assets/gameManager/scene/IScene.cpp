#include "IScene.h"

//初期化
void IScene::Initialize(Create* create) { create_ = create; }

//更新
void IScene::Update() { UpdateViewProjection(); }

// 終了フラグのゲッター
bool IScene::IsFinished() { return isFinished_; }

// 終了フラグ
void IScene::SetIsFinished(bool isFinished) { isFinished_ = isFinished; }

//当たり判定の計算
void IScene::CheckCollision() {}

//デバックカメラの切り替え
void IScene::SwichDebugCamera() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_UP) && input_->PushKey(DIK_LSHIFT)) {
		isDebugCameraActive_ ^= true;
	}
#endif // _DEBUG
}

//デバックカメラの更新
void IScene::DebugCameraUpdate() {
	debugCamera_->Update(); // デバックカメラの更新
	viewProjection_.matView = debugCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();
}

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

	// カメラ
	cameraWorldTransform_.Initialize(); // カメラのワールドトランスフォームの初期化
	// レールカメラ
	railCamera_ = std::make_unique<RailCamera>();                                                                // レールカメラの生成
	railCamera_->Initialize(cameraWorldTransform_.matWorld_, cameraWorldTransform_.rotation_, &viewProjection_); // レールカメラの初期化
	// 追従カメラ
	followCamera_ = std::make_unique<FollowCamera>(); // 追従カメラの生成
	followCamera_->Initialize();                      // 追従カメラの初期化
}

// デバックカメラの動き
void IScene::UpdateViewProjection() {
	//デバックカメラの切り替え
	SwichDebugCamera();
	if (isDebugCameraActive_) {
		//デバックカメラの更新
		DebugCameraUpdate();
	} else {
		if (isFollowOn) {//追従
			viewProjection_.matView = followCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		} else {//レイルカメラ
			viewProjection_.matView = railCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		}
		// 行列の更新
		viewProjection_.TransferMatrix();
	}
	if (input_->GetInstance()->TriggerKey(DIK_SPACE)) {
		isFinished_ = true;
	}
}
