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
#include "assets/gameManager/Log/Log.h"
#include "assets/gameManager/camera/Camera.h"
#include "assets/gameManager/math/Math.h"
#include "assets/gameManager/math/collison/Collision.h"
#include "assets/gameManager/modelCreate/Create.h"

// C++のライブラリ
#include <array>
#include <cassert>
#include <memory>
#include <vector>

typedef struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
}Transform;

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
	virtual void Draw() = 0;

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	IScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="create"></param>
	virtual void Initialize(Create* create);

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

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

	/// <summary>
	/// 当たり判定を計算
	/// </summary>
	virtual void CheckCollision();

private: // メンバ関数
	/// <summary>
	/// デバックカメラの切り替え
	/// </summary>
	void SwichDebugCamera();

	/// <summary>
	/// デバックカメラの更新
	/// </summary>
	void DebugCameraUpdate();

	/// <summary>
	/// デバックカメラ
	/// </summary>
	void UpdateViewProjection();

protected: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	ViewProjection viewProjection_;                      // ビュープロジェクション
	bool isDebugCameraActive_ = false;                   // デバックカメラをオンにするか
	std::unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ
	Create* create_ = nullptr;                           // クリエイトクラス
	bool isFinished_ = false;                            // 終了フラグ
	uint32_t sceneNo_ = 0;                               // シーンナンバー
	int cameraMode_ = (int)CameraMode::kFollow;            // カメラモード
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// カメラ
	std::unique_ptr<Camera> camera_ = nullptr;
	Transform cameraTransform_ = {};
	Matrix4x4 cameraMatWorld_ = {};
};
