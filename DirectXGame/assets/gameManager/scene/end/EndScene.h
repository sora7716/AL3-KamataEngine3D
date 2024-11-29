#pragma once
#include "assets/gameManager/scene/IScene.h"

/// <summary>
/// エンドシーン
/// </summary>
class EndScene :public IScene{

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	EndScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EndScene();

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
