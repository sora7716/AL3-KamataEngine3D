#pragma once
// シーン
#include "assets/gameManager/controller/Controller.h"
#include "assets/gameManager/scene/IScene.h"

// ゲームモデル
#include "assets/failLoad/map/MapChipField.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/Enemy/Enemy.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/magic/luminous/Luminous.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/IEnvironment.h"
#include "assets/gameManager/scene/game/battle/gameObject/particle/Particle.h"

/// <summary>
/// バトルシーン
/// </summary>
class BattleScene : public IScene {
public: // 列挙型
	enum class Type {
		kSkydome,
		kGround,
	};

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	BattleScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BattleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Create* create) override;

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

	// OBB
	OBB* obb_ = nullptr;
	// 六角形
	Hexagon* hexagon_ = nullptr;
	// 球
	Sphere* sphere_ = nullptr;

	// マップ
	std::unique_ptr<MapChipField> mapChipField_ = nullptr;

	// 環境
	std::unique_ptr<IEnvironment> environments_[2] = {nullptr};

	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;

	// パーティクル
	std::unique_ptr<Luminous> luminous_ = nullptr;
	std::unique_ptr<Particle> particle_ = nullptr;

	// コントローラーのタイプ
	Controller* controller_ = nullptr;
	bool isSelectContorol_ = false;

	// ミミック
	std::unique_ptr<Mimic> enemy_ = nullptr;
};
