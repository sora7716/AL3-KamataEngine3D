#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"


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

public://メンバ変数
	Sprite* sprite_ = nullptr;//2Dの描画に使う
	Model* model_ = nullptr;//3Dの描画に使う

	WorldTransform worldTransform_;//ワールドトランスフォーム
	ViewProjection viewProjection_;//ビュープロジェクション

	DebugCamera* debugCamera_ = nullptr;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle2D_ = 0;//テクスチャハンドル
	uint32_t textureHandle3D_ = 0;//テクスチャハンドル

	uint32_t soundDateHandle_ = 0;//サウンドハンドル
	uint32_t voiceHandle_ = 0;//音声再生ハンドル

	float inputFloat3[3] = {};//ImGuiで値を入力する変数

	
	Vector2 screenSize = {WinApp::kWindowHeight, WinApp::kWindowHeight};


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
