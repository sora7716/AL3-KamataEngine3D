#pragma once
#include "assets/gameManager/scene/IScene.h"

/// <summary>
/// ゲームシーンの管理
/// </summary>
class GameManager final{
public: // 列挙型
	enum class Scene {
		kTitle,  // タイトルシーン
		kSearch, // 探索シーン
		kBattle, // バトルシーン
		kEnd,    // エンドシーン
		SceneNum // シーンの数
	};

public: // メンバ関数

	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//コピーコンストラクタを禁止
	GameManager(const GameManager& gameManager) = delete;
	//代入演算子を禁止
	GameManager& operator=(const GameManager& gameManager) = delete;

private://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameManager() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameManager() = default;

public: // 静的メンバ変数
	static inline const int32_t kSceneNum = static_cast<int32_t>(Scene::SceneNum); // シーンの数

private: // メンバ変数
	// 現在のシーンナンバー
	Scene currentScene_ = Scene::kTitle;
	//現在のシーンのナンバー
	int32_t sceneNo_ = 0;
	// シーンのインスタンス
	unique_ptr<IScene> scenes_[kSceneNum] = {nullptr};
};
