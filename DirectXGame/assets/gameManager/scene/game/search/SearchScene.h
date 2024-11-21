#pragma once
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameObject/environment/IEnvironment.h"
#include "assets/gameObject/character/player/Player.h"
#include "assets/controller/Controller.h"

/// <summary>
/// 探索シーン
/// </summary>
class SearchScene : public IScene {
public://列挙型
	enum class Type {
		kSkydome,
		kGround,
	};

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
	/// </summary>]
	
	//環境
	std::unique_ptr<IEnvironment> environments_[2] = {nullptr};

	//プレイヤー
	std::unique_ptr<Player> player_ = nullptr;

	//コントローラーのタイプ
	std::unique_ptr<Controller> control_ = nullptr;
	bool isSelectContorol_ = false;
};
