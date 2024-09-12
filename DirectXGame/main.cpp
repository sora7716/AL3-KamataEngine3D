#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "asset/scene/game/GameScene.h"

#include "asset/scene/result/ResultScene.h"
#include "asset/scene/title/TitleScene.h"
enum class Scene { kUnknow = 0, kTitle, kGame, kResult };
// 現在のシーン
Scene scene = Scene::kUnknow;
GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
ResultScene* resultScene = nullptr;
static int gameScore = 0;
static int highScore = 0;

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene == nullptr) {
			titleScene = new TitleScene();
			titleScene->Initialize();
		} else if (titleScene->IsFinished()) {
			// シーンの切り替え
			scene = Scene::kGame;
			titleScene->BGMStop();
			// 旧シーンの削除
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene();
			gameScene->Initialize();
			gameScene->SetIsFinished(false);
			gameScene->SetHighScore(highScore);
		}

		break;
	case Scene::kGame:
		if (gameScene == nullptr) {
			gameScene = new GameScene();
			gameScene->Initialize();
		} else if (gameScene->IsFinished()) {
			// シーンの切り替え
			scene = Scene::kResult;
			gameScene->BGMStop();
			gameScore = (int)gameScene->GetScore();
			highScore = gameScene->GetHighScore();
			// 旧シーンの削除
			delete gameScene;
			gameScene = nullptr;
			// 新シーンの生成と初期化
			resultScene = new ResultScene();
			resultScene->Initialize();
			resultScene->SetIsFinished(false);
			resultScene->SetScore(gameScore);
		}

		break;
	case Scene::kResult:

		if (resultScene == nullptr) {
			resultScene = new ResultScene();
			resultScene->Initialize();
		} else if (resultScene->IsFinished()) {
			scene = Scene::kTitle;
			resultScene->BGMStop();
			delete resultScene;
			resultScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene();
			titleScene->Initialize();
			titleScene->SetIsFinished(false);
		}

		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		// タイトルシーンの毎フレーム処理
		titleScene->Update();
		break;
	case Scene::kGame:
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
		break;
	case Scene::kResult:
		// リザルトシーンのマイフレーム処理
		resultScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		// タイトルシーンの描画
		titleScene->Draw();
		break;
	case Scene::kGame:
		// ゲームシーンの描画
		gameScene->Draw();
		break;
	case Scene::kResult:
		// リザルトシーンのマイフレーム処理
		resultScene->Draw();
		break;
	}
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"6002_オチのない落ち");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	//// タイトルシーンの初期化
	scene = Scene::kTitle;
	// titleScene = new TitleScene();

	//// ゲームシーンの初期化
	// gameScene = new GameScene();

	////
	// resultScene = new ResultScene();

#ifdef _DEBUG
	// scene = Scene::kGame;
#endif // ゲームシーンからスタート

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// シーンの切り替え
		ChangeScene();
		UpdateScene();
		if (input->TriggerKey(DIK_F10)) {
			win->SetFullscreen(true);
		} else if (input->TriggerKey(DIK_F11)) {
			win->SetFullscreen(false);
		}
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// タイトルシーン描画
		DrawScene();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete titleScene;
	delete gameScene;
	delete resultScene;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}