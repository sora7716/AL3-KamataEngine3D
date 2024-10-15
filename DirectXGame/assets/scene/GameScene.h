#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "assets/create/Create.h"
#include "assets/gameObject/Hexagon/Hexagon.h"
#include "assets/gameObject/camera/RailCamera.h"

#include <memory>
#include <vector>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
public: // 列挙型
	// フィールドの状態
	enum class FieldStatus {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	// ゲームのフェーズ
	enum class GamePhase {
		kStart,
		kMain,
		kEnd,
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

private: // メンバ関数
	/// <summary>
	/// デバックカメラ
	/// </summary>
	void DebugCameraMove();

public:  // 静的メンバ変数
private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	ViewProjection viewProjection_;                      // ビュープロジェクション
	bool isDebugCameraActive_ = false;                   // デバックカメラをオンにするか
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ
	Create* create_ = nullptr;                           // クリエイトクラス
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// カメラ
	std::unique_ptr<RailCamera> railCamera_ = nullptr;
	WorldTransform cameraWorldTransform_;

	// 六角形
	std::unique_ptr<Hexagon> hexagon_ = nullptr;
};
