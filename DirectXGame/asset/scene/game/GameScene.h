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
};
