#include "IScene.h"

// 初期化
void IScene::Initialize(Create* create) { create_ = create; }

// 更新
void IScene::Update() {
	UpdateViewProjection();
#ifdef _DEBUG
	ImGui::Text("LShift & UP : debugMode");
	ImGui::Text("LShift & Space : SceneChange");
#endif // _DEBUG
}

// 終了フラグのゲッター
bool IScene::IsFinished() { return isFinished_; }

// 終了フラグ
void IScene::SetIsFinished(bool isFinished) { isFinished_ = isFinished; }

// 当たり判定の計算
void IScene::CheckCollision() {}

// デバックカメラの切り替え
void IScene::SwichDebugCamera() {
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_UP) && input_->PushKey(DIK_LSHIFT)) {
		isDebugCameraActive_ ^= true;
	}
#endif // _DEBUG
}

// デバックカメラの更新
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
	camera_ = std::make_unique<Camera>();
	cameraTransform_ = {
	    .scale = {1.0f, 1.0f, 1.0f},
          .rotate = {},
          .translate = {}
    };
	cameraMatWorld_ = Math::MakeAffineMatrix(cameraTransform_.scale, cameraTransform_.rotate, cameraTransform_.translate);
	camera_->Initialize(&cameraMatWorld_,&cameraTransform_.rotate);
	camera_->SetTarget(nullptr);
}

// デバックカメラの動き
void IScene::UpdateViewProjection() {
	// デバックカメラの切り替え
	SwichDebugCamera();
	if (isDebugCameraActive_) {
		// デバックカメラの更新
		DebugCameraUpdate();
	} else {
		viewProjection_.matView = camera_->GetViewProjection().matView;
		viewProjection_.matProjection = camera_->GetViewProjection().matProjection;
		// 行列の更新
		viewProjection_.TransferMatrix();
	}
#ifdef _DEBUG
	if (input_->GetInstance()->TriggerKey(DIK_SPACE) && input_->GetInstance()->PushKey(DIK_LSHIFT)) {
		isFinished_ = true;
	}
	if (input_->GetInstance()->TriggerKey(DIK_F) && input_->GetInstance()->PushKey(DIK_LSHIFT)) {
		cameraMode_ = (int)CameraMode::kFollow;
	}
	else if (input_->GetInstance()->TriggerKey(DIK_R) && input_->GetInstance()->PushKey(DIK_LSHIFT)) {
		cameraMode_ = (int)CameraMode::kRail;
	}
	camera_->DebugText();
	ImGui::Begin("Camera");
	ImGui::Text("CameraMode : %d\n0 = rail , 1 = follow", cameraMode_);
	ImGui::End();
#endif // _DEBUG
}
