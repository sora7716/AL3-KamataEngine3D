#pragma once

// KamataEngineにもともとあるもの
#include "Audio.h"
#include "AxisIndicator.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "PrimitiveDrawer.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// 自分で作ったもの
#include "assets/create/Create.h"
#include "assets/gameObject/camera/RailCamera.h"
#include "assets/math/Math.h"
#include "assets/math/collision/Collision.h"

// C++のライブラリ
#include <cassert>
#include <memory>
#include <vector>

/// <summary>
/// シーンのインターフェース
/// </summary>
class IScene {

public: // 列挙型

	// ゲームのフェーズ
	enum class GamePhase {
		kStart,
		kMain,
		kEnd,
	};

public: // 純粋仮想関数

	virtual ~IScene() = default;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

public: // メンバ関数

	/// <summary>
	/// 終了フラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool IsFinished();

	/// <summary>
	/// 終了フラグのセッター
	/// </summary>
	/// <param name="isFinished">終了フラグ</param>
	void SetIsFinished(bool isFinished);

protected: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	IScene();

	/// <summary>
	/// デバックカメラ
	/// </summary>
	void DebugCameraMove();

protected: // メンバ変数

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	ViewProjection viewProjection_;                 // ビュープロジェクション
	bool isDebugCameraActive_ = false;              // デバックカメラをオンにするか
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ
	Create* create_ = nullptr;                      // クリエイトクラス
	bool isFinished_ = false;                        // 終了フラグ

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// カメラ
	std::unique_ptr<RailCamera> railCamera_ = nullptr;
	WorldTransform cameraWorldTransform_;
};
