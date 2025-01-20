#pragma once
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/skydome/Skydome.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/ground/Ground.h"

/// <summary>
/// 探索シーン
/// </summary>
class SearchScene : public IScene {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	SearchScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SearchScene();

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
	
	// 天球
	std::unique_ptr<IEnvironment> skyDome_ = nullptr;
	// 地面
	std::unique_ptr<IEnvironment> ground_ = nullptr;
};
