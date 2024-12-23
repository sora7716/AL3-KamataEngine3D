#include "GameManager.h"
#include "scene/end/EndScene.h"
#include "scene/game/battle/BattleScene.h"
#include "scene/game/search/SearchScene.h"
#include "scene/title/TitleScene.h"

//コンストラクタ
GameManager::GameManager() {
	// ログの生成
	Log::GetInstance()->Initialize();
}

//デストラクタ
GameManager::~GameManager() {
	// ゲームの終了をログに書き込む
	Log::GetInstance()->AddLog("ゲームが終了しました");
}

// インスタンスのゲッター
GameManager* GameManager::GetInstance() {
	// 関数内にstatic変数として宣言
	static GameManager instance;

	return &instance;
}

// 初期化
void GameManager::Initialize() {
	if (!create_) {
		Log::GetInstance()->AddLog("モデルの生成を開始します");
		CreateModel();
		Log::GetInstance()->AddLog("モデルの生成が成功しました");
	}
	// シーンのナンバーを検出
	sceneNo_ = static_cast<int32_t>(currentScene_);
	// タイトルシーン
	if (currentScene_ == Scene::kTitle) {
		if (scenes_[sceneNo_] == nullptr) {
			Log::GetInstance()->AddLog("タイトルシーンの生成を開始します");
			scenes_[sceneNo_] = std::make_unique<TitleScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("タイトルシーンの生成が成功しました");
		} else if (scenes_[sceneNo_]->IsFinished()) {
			Log::GetInstance()->AddLog("タイトルシーンが終了しました");
			Log::GetInstance()->AddLog("タイトルシーンを削除します");
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			Log::GetInstance()->AddLog("タイトルシーンの削除が成功しました");	
			// シーンの切り替え
			currentScene_ = Scene::kSearch;
			Log::GetInstance()->AddLog("探索シーンの生成を開始します");	
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<SearchScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("探索シーンの生成が成功しました");	
		}
	}
	// 探索シーン
	else if (currentScene_ == Scene::kSearch) {
		if (scenes_[sceneNo_] == nullptr) {
			Log::GetInstance()->AddLog("探索シーンの生成を開始します");
			scenes_[sceneNo_] = std::make_unique<SearchScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("探索シーンの生成が成功しました");
		} else if (scenes_[sceneNo_]->IsFinished()) {
			Log::GetInstance()->AddLog("探索シーンが終了しました");
			Log::GetInstance()->AddLog("探索シーンを削除します");
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			Log::GetInstance()->AddLog("探索シーンの削除が成功しました");
			// シーンの切り替え
			currentScene_ = Scene::kBattle;
			Log::GetInstance()->AddLog("バトルシーンを生成します");
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<BattleScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("バトルシーンの生成が成功しました");
		}
	}
	// バトルシーン
	else if (currentScene_ == Scene::kBattle) {
		if (scenes_[sceneNo_] == nullptr) {
			Log::GetInstance()->AddLog("バトルシーンを生成します");
			scenes_[sceneNo_] = std::make_unique<BattleScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("バトルシーンの生成が成功しました");
		} else if (scenes_[sceneNo_]->IsFinished()) {
			Log::GetInstance()->AddLog("バトルシーンが終了しました");
			Log::GetInstance()->AddLog("バトルシーンの削除を開始します");
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			Log::GetInstance()->AddLog("バトルシーンの削除が成功しました");
			// シーンの切り替え
			currentScene_ = Scene::kEnd;
			Log::GetInstance()->AddLog("エンドシーンを生成します");
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<EndScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("エンドシーンの生成が成功しました");
		}
	}
	// エンドシーン
	else if (currentScene_ == Scene::kEnd) {
		if (scenes_[sceneNo_] == nullptr) {
			Log::GetInstance()->AddLog("エンドシーンを生成します");
			scenes_[sceneNo_] = std::make_unique<EndScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("エンドシーンの生成が成功しました");
		} else if (scenes_[sceneNo_]->IsFinished()) {
			Log::GetInstance()->AddLog("エンドシーンの終了しました");
			Log::GetInstance()->AddLog("エンドシーンの削除を開始します");
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			Log::GetInstance()->AddLog("エンドシーンの削除が成功しました");
			// シーンの切り替え
			currentScene_ = Scene::kTitle;
			Log::GetInstance()->AddLog("タイトルシーンを生成します");
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<TitleScene>();
			scenes_[sceneNo_]->Initialize(create_);
			Log::GetInstance()->AddLog("タイトルシーンを生成が成功しました");
		}
	}
}

// 更新
void GameManager::Update() {
#ifdef _DEBUG
	ImGui::Text("%d", sceneNo_);
#endif // _DEBUG

	// タイトルシーン
	if (currentScene_ == Scene::kTitle) {
		scenes_[sceneNo_]->Update();
	}
	// 探索シーン
	else if (currentScene_ == Scene::kSearch) {
		scenes_[sceneNo_]->Update();

	}
	// バトルシーン
	else if (currentScene_ == Scene::kBattle) {
		scenes_[sceneNo_]->Update();

	}
	// エンドシーン
	else if (currentScene_ == Scene::kEnd) {
		scenes_[sceneNo_]->Update();
	}
}

// 描画
void GameManager::Draw() {
	// タイトルシーン
	if (currentScene_ == Scene::kTitle) {
		scenes_[sceneNo_]->Draw();
	}
	// 探索シーン
	else if (currentScene_ == Scene::kSearch) {
		scenes_[sceneNo_]->Draw();
	}
	// バトルシーン
	else if (currentScene_ == Scene::kBattle) {
		scenes_[sceneNo_]->Draw();
	}
	// エンドシーン
	else if (currentScene_ == Scene::kEnd) {
		scenes_[sceneNo_]->Draw();
	}
}

// モデルの生成
void GameManager::CreateModel() {
	create_ = Create::GetInstance();
	create_->TextureCreate();
	create_->TitleSceneModel();
	create_->GameSceneModel();
	create_->EndSceneModel();
}
