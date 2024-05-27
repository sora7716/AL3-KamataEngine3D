#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <vector>
#include "DebugCamera.h"
#include "gameObject/skydome/Skydome.h"
#include "gameObject/player/Player.h"
#include"gameObject/blocks/Blocks.h"
#include"gameObject/mapChipField/MapChipField.h"
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
	Model* modelBlock_ = nullptr;//ブロックのモデル
	uint32_t blockTextureHandle_= 0;//ブロックのテクスチャ
	Blocks* blocks_ = nullptr;//ブロック
	ViewProjection viewProjection_;//ビュープロジェクション

	bool isDebugCameraActive_ = false;//デバックカメラを切り替えるフラグ
	DebugCamera* debugCamera_ = nullptr;//デバックカメラ
	
	Skydome* skydome_ = nullptr;//スカイドーム
	Model* modelSkydome_ = nullptr;//スカイドームモデル

	MapChipField* mapChipField_ = nullptr;//マップチップフィールド

	Player* player_ = nullptr;         // プレイヤー
	Model* modelPlayer_ = nullptr;     // プレイヤーモデル
	uint32_t playerTextureHandle_ = 0; // プレイヤーのテクスチャ

};
