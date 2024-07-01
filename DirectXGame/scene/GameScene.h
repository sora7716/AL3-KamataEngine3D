#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "gameObject/blocks/Blocks.h"
#include "gameObject/camera/CameraController.h"
#include "gameObject/enemy/Enemy.h"
#include "gameObject/mapChipField/MapChipField.h"
#include "gameObject/player/Player.h"
#include "gameObject/skydome/Skydome.h"
#include "gameObject/particle/DeathParticles.h"
#include <vector>
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

	void GenerateBlocks();

	void CheckAllCollision();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	CameraController* cameraController_ = nullptr; // カメラコントロール

	Skydome* skydome_ = nullptr;    // スカイドーム
	Model* skydomeModel_ = nullptr; // スカイドームモデル

	MapChipField* mapChipField_ = nullptr; // マップチップ

	Model* modelBlock_ = nullptr;      // ブロックのモデル
	uint32_t blockTextureHandle_ = 0u; // ブロックのテクスチャ
	Blocks* blocks_ = nullptr;         // ブロック
	ViewProjection viewProjection_;    // ビュープロジェクション

	Player* player_ = nullptr;          // プレイヤー
	Model* playerModel_ = nullptr;      // プレイヤーモデル
	uint32_t playerTextureHandle_ = 0u; // プレイヤーのテクスチャ

	std::list<Enemy*> enemies_;           // エネミー
	Model* enemyModel_ = nullptr;      // エネミーのモデル
	uint32_t enemyTextureHandle_ = 0u; // エネミーのテクスチャ
	static inline const int kEnemyNum = 1;//エネミーの数

	bool isDebugCameraActive_ = false;   // デバックカメラを切り替えるフラグ
	DebugCamera* debugCamera_ = nullptr; // デバックカメラ

	DeathParticles *deathParticles_ = nullptr;//死んだときのパーティクル
	Model* particleModel_ = nullptr;//パーティクルのモデル
	uint32_t particleTextureHandle_ = 0u;
};
