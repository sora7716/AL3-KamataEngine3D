#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <vector>
#include "gameObject/skydome/Skydome.h"
#include "gameObject/player/Player.h"
#include"gameObject/blocks/Blocks.h"
#include"gameObject/mapChipField/MapChipField.h"
#include "gameObject/camera/CameraController.h"

class DebugCamera;

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

#pragma region 
	Model* modelBlock_ = nullptr;//ブロックのモデル
	uint32_t blockTextureHandle_= 0;//ブロックのテクスチャ
	Blocks* blocks_ = nullptr;//ブロック
	ViewProjection viewProjection_;//ビュープロジェクション
#pragma endregion ブロック

#pragma region
	bool isDebugCameraActive_ = false;//デバックカメラを切り替えるフラグ
	DebugCamera* debugCamera_ = nullptr;//デバックカメラ
#pragma endregion デバックカメラ

#pragma region 
	Skydome* skydome_ = nullptr;//スカイドーム
	Model* modelSkydome_ = nullptr;//スカイドームモデル
#pragma endregion スカイドーム

#pragma region 
	MapChipField* mapChipField_ = nullptr;//マップチップフィールド
#pragma endregion マップチップフィールド

#pragma region
	Player* player_ = nullptr;         // プレイヤー
	Model* modelPlayer_ = nullptr;     // プレイヤーモデル
	uint32_t playerTextureHandle_ = 0; // プレイヤーのテクスチャ
#pragma endregion プレイヤー

#pragma region
	CameraController* cameraController_ = nullptr;//カメラコントロール
#pragma endregion カメラコントロール
};
