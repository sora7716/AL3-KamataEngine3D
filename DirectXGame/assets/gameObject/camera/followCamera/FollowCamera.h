#pragma once
#include "ViewProjection.h"

// 前方宣言
class WorldTransform;

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
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
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns></returns>
	ViewProjection& GetViewProjection();

private://メンバ関数
	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	void GamePadControl();

	/// <summary>
	/// キーボードの操作
	/// </summary>
	void KeyBoaeredControl();

private: // メンバ変数
	ViewProjection viewProjection_;
	// 追従対象
	const WorldTransform* target_ = nullptr;
};
