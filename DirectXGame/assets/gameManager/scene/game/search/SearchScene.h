#pragma once
#include "assets/gameManager/scene/IScene.h"

/// <summary>
/// 探索シーン
/// </summary>
class SearchScene :public IScene{

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
	void Initialize() override;

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
};
