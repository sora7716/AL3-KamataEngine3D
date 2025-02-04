#pragma once
#include "assets/gameManager/scene/IScene.h"
#include "gameObject/environment/honeycomb/Honeycomb.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public IScene {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Create *create) override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//地面
	std::unique_ptr<Honeycomb> honeycomb_ = nullptr;
};
