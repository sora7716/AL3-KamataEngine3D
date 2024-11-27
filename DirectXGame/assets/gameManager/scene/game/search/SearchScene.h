#pragma once
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameObject/ground/ground.h"
#include "assets/gameObject/skydome/SkyDome.h"
#include "assets/gameObject/player/Player.h"
#include "assets/gameObject/enemy/Enemy.h"
#include "assets/gameObject/lockOn/LockOn.h"
#include "assets/gameObject/hammer/Hammer.h"
#include "assets/math/collision/CollisionManager.h"

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

private:

	//モデル生成
	void CreateModel();

	//各オブジェクトの初期化処理
	void InitializeObject();

	//衝突判定と応答
	void CheckAllCollision();

private: // メンバ変数

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// 各モデルのオブジェクト
	std::unique_ptr<Model> modelGround_ = nullptr;
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	std::unique_ptr<Model> modelFighterBody_ = nullptr;
	std::unique_ptr<Model> modelFighterHead_ = nullptr;
	std::unique_ptr<Model> modelFighterL_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterR_arm_ = nullptr;
	std::unique_ptr<Model> modelEnemyBody_ = nullptr;
	std::unique_ptr<Model> modelEnemyL_spear_ = nullptr;
	std::unique_ptr<Model> modelEnemyR_spear_ = nullptr;
	std::unique_ptr<Model> modelHammer_ = nullptr;


	// 地面
	std::unique_ptr<Ground> ground_ = nullptr;
	// 天球
	std::unique_ptr<SkyDome> skyDome_ = nullptr;
	// ハンマー
	std::unique_ptr<Hammer> hammer_ = nullptr;
	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;
	// 敵
	std::list<std::unique_ptr<Enemy>> enemies_;
	// ロックオン
	std::unique_ptr<LockOn> lockOn_ = nullptr;

	//衝突マネージャ
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;
};
