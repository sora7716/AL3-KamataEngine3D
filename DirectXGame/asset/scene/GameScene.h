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
	unique_ptr<Enemy> enemy_ = nullptr;                // 敵
	ViewProjection viewProjection_;                    // ビュープロジェクション
	bool isDebugCameraActive_ = false;                 // デバックカメラをオンにするか
	unique_ptr<DebugCamera> debugCamera_ = nullptr;    // デバックカメラ
	IPlayerCommand* iPlayerCommandBeside_ = nullptr;   // 縦移動の入力を受け取る
	IPlayerCommand* iPlayerCommandVertical_ = nullptr; // 縦移動の入力を受け取る
	IPlayerCommand* iPlayerCommandRotate_ = nullptr;   // 旋回
	unique_ptr<InputHandle> inputHandle_ = nullptr;    // プレイヤーのコマンド
	unique_ptr<Skydome> skydome_ = nullptr;            // スカイドーム
};
