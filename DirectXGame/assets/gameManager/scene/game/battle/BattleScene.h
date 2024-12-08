#pragma once
// シーン
#include "assets/gameManager/scene/game/battle/gameObject/character/player/controller/Controller.h"
#include "assets/gameManager/scene/IScene.h"

// ゲームモデル
#include "assets/failLoad/map/MapChipField.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/Enemy/Enemy.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/IEnvironment.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/magic/luminous/Luminous.h"
#include "assets/gameManager/scene/game/battle/gameObject/particle/Particle.h"

// ワイヤーフレーム
#include "assets/gameManager/scene/game/battle/gameObject/Shape/obb/OBB.h"
#include "assets/gameManager/scene/game/battle/gameObject/Shape/hexagon/Hexagon.h"

//プレイヤーのテクスチャー
#include "assets/gameManager/scene/game/battle/gameObject/ui/LifeBar/LifeBar.h"

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
	void Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// プレイヤーと敵の当たり判定
	/// </summary>
	void CheckPlayerEnemyCollision();

	/// <summary>
	/// プレイヤー攻撃の当たり判定
	/// </summary>
	void CheckPlayerAttack();
private: // メンバ変数
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// OBB
	Shape::OBBMaterial obbMaterial_ = {};
	std::unique_ptr<OBB> obb_ = nullptr;

	// 六角形
	std::unique_ptr<Hexagon> hexagon_ = nullptr;
	Shape::HexagonMaterial hexagonMatrial_ = {};

	// マップ
	std::unique_ptr<MapChipField> mapChipField_ = nullptr;

	// 環境
	std::unique_ptr<IEnvironment> environments_[2] = {nullptr};

	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;

	//パーティクル
	std::unique_ptr<Luminous> luminous_ = nullptr;
	std::unique_ptr<Particle> particle_ = nullptr;

	// コントローラーのタイプ
	Controller* controller_ = nullptr;
	bool isSelectContorol_ = false;

	//ミミック
	std::unique_ptr<Mimic> enemy_ = nullptr;

	//ライフバー
	std::unique_ptr<LifeBar> playerLifeBar_ = nullptr;
	//エネミー
	std::unique_ptr<LifeBar> enemyLifeBar_ = nullptr;

	bool isDead_ = false;
	bool isClear_ = false;
};
