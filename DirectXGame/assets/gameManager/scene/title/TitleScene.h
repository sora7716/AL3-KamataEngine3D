#pragma once
#include "assets/gameManager/scene/IScene.h"

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
	void Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void Animation();

private: // メンバ変数

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	uint32_t textureHandle_ = 0;
	
	std::unique_ptr<Model> model_ = nullptr;
	
	WorldTransform worldTransform_;

};
