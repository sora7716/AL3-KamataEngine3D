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

	void DebugCameraMove();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	unique_ptr<Create> create_ = nullptr;
	unique_ptr<Player> player_ = nullptr;
	unique_ptr<DebugCamera> debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false; // デバックカメラをオンにするか
};
