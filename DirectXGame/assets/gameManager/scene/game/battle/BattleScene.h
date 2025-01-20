#pragma once
// シーン
#include "assets/gameManager/controller/Controller.h"
#include "assets/gameManager/scene/IScene.h"

// ゲームモデル
#include "assets/failLoad/map/MapChipField.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/Enemy/Enemy.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/Player.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/player/magic/luminous/Luminous.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/honeycomb/Honeycomb.h"
#include "assets/gameManager/scene/game/battle/gameObject/environment/skydome/Skydome.h"
#include "assets/gameManager/scene/game/battle/gameObject/particle/Particle.h"
#include "assets/gameManager/scene/game/battle/gameObject/spellcard/SpellCard.h"

/// <summary>
/// バトルシーン
/// </summary>
class BattleScene : public IScene {
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

private: // メンバ関数
	/// <summary>
	/// 当たり判定を計算
	/// </summary>
	void CheckCollision() override;

private: // メンバ変数
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// サーチライト
	Searchlight* serchlight_ = nullptr;

	// マップ
	std::unique_ptr<MapChipField> mapChipField_ = nullptr;

	// 環境
	std::unique_ptr<Skydome> skydome_ = nullptr;
	std::unique_ptr<Honeycomb> ground_ = nullptr;

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

	// スペルカード
	std::unique_ptr<SpellCard> spellCard_ = nullptr;

};
