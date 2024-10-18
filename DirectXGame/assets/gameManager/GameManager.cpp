#include "GameManager.h"
#include "scene/end/EndScene.h"
#include "scene/game/battle/BattleScene.h"
#include "scene/game/search/SearchScene.h"
#include "scene/title/TitleScene.h"

// インスタンスのゲッター
GameManager* GameManager::GetInstance() { 
//関数内にstatic変数として宣言
	static GameManager instance;

	return &instance;
}

// 初期化
void GameManager::Initialize() {
	// シーンのナンバーを検出
	sceneNo_ = static_cast<int32_t>(currentScene_);
	// タイトルシーン
	if (currentScene_ == Scene::kTitle) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<TitleScene>();
			scenes_[sceneNo_]->Initialize();
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kSearch;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<SearchScene>();
			scenes_[sceneNo_]->Initialize();
			scenes_[sceneNo_]->SetIsFinished(false);
		}
	}
	// 探索シーン
	else if (currentScene_ == Scene::kSearch) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<SearchScene>();
			scenes_[sceneNo_]->Initialize();
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kBattle;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<BattleScene>();
			scenes_[sceneNo_]->Initialize();
			scenes_[sceneNo_]->SetIsFinished(false);
		}
	}
	// バトルシーン
	else if (currentScene_ == Scene::kBattle) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<BattleScene>();
			scenes_[sceneNo_]->Initialize();
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kEnd;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<EndScene>();
			scenes_[sceneNo_]->Initialize();
			scenes_[sceneNo_]->SetIsFinished(false);
		}
	}
	// エンドシーン
	else if (currentScene_ == Scene::kEnd) {
		if (scenes_[sceneNo_] == nullptr) {
			scenes_[sceneNo_] = std::make_unique<EndScene>();
			scenes_[sceneNo_]->Initialize();
		} else if (scenes_[sceneNo_]->IsFinished()) {
			// シーンの削除
			scenes_[sceneNo_] = nullptr;
			// シーンの切り替え
			currentScene_ = Scene::kTitle;
			// シーンのナンバーを検出
			sceneNo_ = static_cast<int32_t>(currentScene_);
			scenes_[sceneNo_] = std::make_unique<TitleScene>();
			scenes_[sceneNo_]->Initialize();
			scenes_[sceneNo_]->SetIsFinished(false);
		}
	}
}

// 更新
void GameManager::Update() {
	ImGui::Text("%d", sceneNo_);
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
