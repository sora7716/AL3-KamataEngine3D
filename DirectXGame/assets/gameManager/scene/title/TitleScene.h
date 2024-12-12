#pragma once
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameManager/scene/title/gameObject/titleName/TitleName.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public IScene {

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Create*create) override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// アニメーション
	/// </summary>
	void Animation();

private: // メンバ変数

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	std::unique_ptr<TitleName> titleName_ = nullptr;

};
