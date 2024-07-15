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
#include "gameObject/particle/DeathParticles.h"
#include "gameObject/player/Player.h"
#include "gameObject/skydome/Skydome.h"
#include "scene/sceneManage/fade/Fade.h"
#include <vector>
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // 構造体など

	//フェズの状態
	enum class FadePhase {
		kFadeIn,//フェードイン
		kMain,//メイン部
		kFadeOut,//フェードアウト
	};

	
	// ゲームフェーズの型
	enum class Phase {
		kPlay,  // ゲームプレイ
		kDeath, // 死亡演出
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
	/// ブロックを出す初期化処理をまとめた
	/// </summary>
	void GenerateBlocks();

	/// <summary>
	/// カメラの更新
	/// </summary>
	void CameraUpdate();

	/// <summary>
	/// 敵とプレイヤーが当たっているかどうかの関数
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// フェーズの変更
	/// </summary>
	void ChangePhaseUpdate();

	/// <summary>
	/// フェードを入れたフェーズの変更
	/// </summary>
	void ChangeFadePhaseUpdate();

	/// <summary>
	/// フェーズの変更
	/// </summary>
	void ChangePhaseDraw();

	/// <summary>
	/// デスフラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool IsDeath() const;

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

	std::list<Enemy*> enemies_;            // エネミー
	Model* enemyModel_ = nullptr;          // エネミーのモデル
	uint32_t enemyTextureHandle_ = 0u;     // エネミーのテクスチャ
	static inline const int kEnemyNum = 1; // エネミーの数

	bool isDebugCameraActive_ = false;   // デバックカメラを切り替えるフラグ
	DebugCamera* debugCamera_ = nullptr; // デバックカメラ

	DeathParticles* deathParticles_ = nullptr; // 死んだときのパーティクル
	Model* particleModel_ = nullptr;           // パーティクルのモデル
	uint32_t particleTextureHandle_ = 0u;      // パーティクルのテクスチャ

	Phase phase_ = Phase::kPlay; // ゲームの現在のフェーズ
	FadePhase fadePhase_ = FadePhase::kFadeIn;//フェードの現在のフェーズ
	bool isDeath_ = false;       // デスフラグ

	bool finished_ = false; // 終了フラグ

	Fade* fade_ = nullptr;//フェード

	bool isFadeIni = true;

public://メンバ変数
	static inline const float kFadeTime = 5.0f;//フェードする時間
};
