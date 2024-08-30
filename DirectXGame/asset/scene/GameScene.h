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
#include <sstream>
#include <memory>
using namespace std;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

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
};
