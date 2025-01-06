#pragma once
#include "ViewProjection.h"


// 前方宣言
class WorldTransform;
class Player;

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {

public:
	/// <summary>
	/// カメラフェーズ
	/// </summary>
	enum class CameraPhase { kCameraController, kFollow };

	// 矩形
	struct Rect {
		float left = 0.0f;   // 左端
		float right = 1.0f;  // 右端
		float bottom = 0.0f; // 下端
		float top = 1.0f;    // 上端
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FollowCamera() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~FollowCamera() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 追従対処のセッター
	/// </summary>
	/// <param name="target">ターゲット</param>
	void SetTarget(const WorldTransform* target);

	/// <summary>
	/// 追従対象のセッタ－
	/// </summary>
	/// <param name="player"></param>
	void SetTarget(Player* target) { targetPlayer_ = target; }

	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns></returns>
	ViewProjection& GetViewProjection();

	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	void GamepadControl();

	/// <summary>
	/// キーボードの操作
	/// </summary>
	void KeyboardControl();

	/// <summary>
	/// 追従カメラの更新処理
	/// </summary>
	void FollowCameraUpdate();

	/// <summary>
	/// カメラ制御の更新処理
	/// </summary>
	void CameraControllerUpdate();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// カメラ移動範囲
	/// </summary>
	/// <param name="area">範囲</param>
	void SetMovableArea(Rect area) { movableArea_ = area; }

private: // メンバ変数
	ViewProjection viewProjection_;
	// 追従対象
	const WorldTransform* target_ = nullptr;
	// 追従対象(プレイヤー)
	Player* targetPlayer_ = nullptr;
	// 追従対象とカメラの座標の差(オフセット)
	Vector3 targetOffset_ = {0, 5, -12.0f};
	// カメラの切り替え
	bool isCameraExChange_ = false;
	// カメラフェーズ(最初はカメラ制御)
	CameraPhase cameraPhase_ = CameraPhase::kCameraController;
	// カメラ更新処理のテーブル
	static void (FollowCamera::*cameraUpdateTable[])();
	// カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};
	// カメラの目標座標
	Vector3 targetPos_ = {};
	// 座標補間割合
	static inline const float kInterpokationRate_ = 0.35f;
};
