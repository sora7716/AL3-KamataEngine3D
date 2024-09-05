#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "asset/create/Create.h"
#include "asset/gameObject/player/Player.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/player/command/ICommand.h"
#include "asset/gameObject/player/command/InputHandler.h"
#include "asset/gameObject/enemy/Enemy.h"
#include "asset/gameObject/player/playerParts/PlayerParts.h"

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

private://メンバ関数

	/// <summary>
	/// デバックカメラ
	/// </summary>
	void DebugCameraMove();

	/// <summary>
	/// プレイヤーのパーツを作る
	/// </summary>
	void Create_PlayerParts();

	/// <summary>
	/// コマンドを受け取る
	/// </summary>
	void InputCommand();

	/// <summary>
	/// コマンドの更新
	/// </summary>
	void UpdateCommand();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	ViewProjection viewProjection_;                 // ビュープロジェクション
	bool isDebugCameraActive_ = false;              // デバックカメラをオンにするか
	unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//クリエイトクラス
	unique_ptr<Create> create_ = nullptr;
	//プレイヤークラス
	unique_ptr<Player> player_ = nullptr;
	//レールカメラ
	unique_ptr<RailCamera> railCamera_ = nullptr;
	WorldTransform railCameraWorldTransform_;
	//コマンド
	ICommand * lateralMovement_ = nullptr;//横移動
	ICommand * verticalMvement_ = nullptr;//縦移動
	//インプットハンドラ
	unique_ptr<InputHandler> inputHandler_ = nullptr;
	//障害物
	unique_ptr<Enemy> enemy_ = nullptr;
	unique_ptr<IPlayerParts> playerParts_[IPlayerParts::PartsNum] = {nullptr};
};
