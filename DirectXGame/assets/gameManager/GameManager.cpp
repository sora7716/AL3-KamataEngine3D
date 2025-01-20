#include "GameManager.h"
#include "scene/end/EndScene.h"
#include "scene/game/battle/BattleScene.h"
#include "scene/title/TitleScene.h"

//コンストラクタ
GameManager::GameManager() {
	// ログの生成
	Log::GetInstance()->Initialize();
}

//デストラクタ
GameManager::~GameManager() {
	// ゲームの終了をログに書き込む
	Log::GetInstance()->AddLog(LogLevels::kInformation, "ゲームを終了しました");
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
		Log::GetInstance()->AddLog(LogLevels::kInformation,"モデルの生成を開始します");
		CreateModel();
		Log::GetInstance()->AddLog(LogLevels::kInformation,"モデルの生成が成功しました");
	}
	// シーンのナンバーを検出
	sceneNo_ = static_cast<int32_t>(currentScene_);
	// タイトルシーン
	if (currentScene_ == Scene::kTitle) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<TitleScene>();
			scenes_[sceneNo_]->Initialize(create_);
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kBattle;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<BattleScene>();
			scenes_[sceneNo_]->Initialize(create_);
		}
	}
	// バトルシーン
	else if (currentScene_ == Scene::kBattle) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<BattleScene>();
			scenes_[sceneNo_]->Initialize(create_);
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kEnd;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<EndScene>();
			scenes_[sceneNo_]->Initialize(create_);
		}
	}
	// エンドシーン
	else if (currentScene_ == Scene::kEnd) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<EndScene>();
			scenes_[sceneNo_]->Initialize(create_);
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kTitle;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<TitleScene>();
			scenes_[sceneNo_]->Initialize(create_);
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
