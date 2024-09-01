#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "asset/command/InputHandle.h"
#include "asset/create/Create.h"
#include "asset/gameObject/enemy/Enemy.h"
#include "asset/gameObject/player/Player.h"
#include "asset/math/collision/Collision.h"
#include "asset/gameObject/skydome/Skydome.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/enemy/bullet/EnemyBullet.h"
#include "asset/gameObject/player/bullet/PlayerBullet.h"
#include "asset/gameObject/ground/Ground.h"
#include "asset/gameObject/fade_image/Fade.h"
#include "asset/gameObject/effect/DeathParticles.h"
#include <sstream>
#include <memory>
using namespace std;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public://列挙型

	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	enum class Status { 
		kPlay,//生存 
		kDeth,//死んだ
	};

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	
	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵弾モデルのゲッター
	/// </summary>
	/// <returns>敵弾モデル</returns>
	Model* GetEnemyBulletModel() const;

	/// <summary>
	/// 自弾を追加する
	/// </summary>
	/// <param name="playerBullet">自弾</param>
	void AddPlayerBullet(PlayerBullet* playerBullet);

	/// <summary>
	/// 自弾モデルのゲッター
	/// </summary>
	/// <returns>敵弾モデル</returns>
	Model* GetPlayerBulletModel() const;

	/// <summary>
	/// 終了フラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool IsFinished() const;

	/// <summary>
	/// 終了フラグのセッター
	/// </summary>
	/// <param name="isFinished"></param>
	void SetIsFinished(const bool& isFinished);

private: // メンバ関数
	/// <summary>
	/// キー入力のコマンドの初期化
	/// </summary>
	void InputCommandInitialize();

	/// <summary>
	/// プレイヤーの移動のコマンドをまとめた
	/// </summary>
	void PlayerActionCommand();

	/// <summary>
	/// デバックカメラ
	/// </summary>
	void DebugCameraMove();

	/// <summary>
	/// 衝突判定の応答
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopDate();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	/// <summary>
	/// 更新のフェーズ
	/// </summary>
	void ChangeUpdate();

	/// <summary>
	/// 描画のフェーズ
	/// </summary>
	void ChangeDraw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	static inline const float kFadeTime = 5; // フェードをしてほしい時間
	static inline const float kEnemyNum = 6;//敵の数
	/// <summary>
	/// ゲームシーン用
	/// </summary>

public: // メンバ変数

	unique_ptr<Create> create_ = nullptr;              // テクスチャやモデルを生成
	unique_ptr<Player> player_ = nullptr;              // プレイヤー
	list<Enemy*> enemies_;                             // 敵(複数)
	Enemy* enemy_;                                     // 敵(単体)
	ViewProjection viewProjection_;                    // ビュープロジェクション
	bool isDebugCameraActive_ = false;                 // デバックカメラをオンにするか
	unique_ptr<DebugCamera> debugCamera_ = nullptr;    // デバックカメラ
	IPlayerCommand* iPlayerCommandBeside_ = nullptr;   // 縦移動の入力を受け取る
	IPlayerCommand* iPlayerCommandVertical_ = nullptr; // 縦移動の入力を受け取る
	IPlayerCommand* iPlayerCommandRotate_ = nullptr;   // 旋回
	unique_ptr<InputHandle> inputHandle_ = nullptr;    // プレイヤーのコマンド
	unique_ptr<Skydome> skydome_ = nullptr;            // スカイドーム
	unique_ptr<RailCamera> railCamera_ = nullptr;      // レールカメラ
	WorldTransform railCameraWorldTransform_;          // レールカメラのワールドトランスフォーム
	list<EnemyBullet*> enemyBullets_;                  // 敵弾
	list<PlayerBullet*> playerBullets_;                // 自弾
	stringstream enemyPopCommands;                     // 敵発生コマンド
	bool isEnemyWaite_ = false;                        // 待機フラグ
	int32_t enemyWaitTime_ = 0;                        // 待機時間
	unique_ptr<Ground> ground_ = nullptr;              // 地面
	bool isFinished_ = false;                            // 終了フラグ
	unique_ptr<Fade> fade_ = nullptr;                  // フェード
	Phase phase_ = Phase::kFadeIn;                     // 現在のシーンのフェーズ
	unique_ptr<DeathParticles> playerDethParticle_ = nullptr; // デスパーティクル
	Status playerStatus_ = Status::kPlay;               // プレイヤーの状態
};
