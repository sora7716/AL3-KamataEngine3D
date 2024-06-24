#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "scene/calculate/Aithmetic.h"

typedef struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
} Rect;

// 前方宣言
class Player; // #include "Player.h"の代わり(この宣言の方法の場合インスタンスをポインタにしないといけない)

class CameraController {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns></returns>
	ViewProjection& GetViewProjection();

	/// <summary>
	/// ターゲットのセッター
	/// </summary>
	/// <param name="target">追従したい対象</param>
	void SetTarget(Player* target);

	/// <summary>
	/// MovableAreaのセッター
	/// </summary>
	/// <param name="area"></param>
	void SetMovableArea(Rect area);

	static inline const float kInterpolationRate = 0.9f; // カメラの追従を少し遅くする(0～1で判定)
	static inline const float kVelocityBias = 100.0f;
	static inline const Rect margin = {5.0f, 10.0f, 5.0f, 10.0f};

private:
	ViewProjection viewProjection_; // ビュープロジェクション
	Player* target_ = nullptr;      // プレイヤークラス

	Vector3 targetOffset_ = {}; // ターゲットから少し離す

	Vector3 goalPosition_ = {}; // 目標ポジション

	Rect movableArea_ = {0, 100, 0, 100}; // 追従する範囲
};