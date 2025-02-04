#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// カメラクラス
/// </summary>
class Camera {
public: // 列挙型
	enum class Mode { kRail, kFollow };

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Camera() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera() = default;

	/// <summary>
	/// カメラの初期化
	/// </summary>
	/// <param name="matWorld">ワールド行列</param>
	/// <param name="rotate">回転</param>
	void Initialize(const Matrix4x4* matWorld, const Vector3* rotate);

	/// <summary>
	/// レイルカメラの更新
	/// </summary>
	void RailUpdate();

	/// <summary>
	/// フォローカメラの更新
	/// </summary>
	void FollowUpdate();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 追従対処のセッター
	/// </summary>
	/// <param name="target">ターゲット</param>
	void SetTarget(const WorldTransform* target);

	/// <summary>
	/// ビュープロジェクションのゲッター
	/// </summary>
	/// <returns>ビュープロジェクション</returns>
	const ViewProjection& GetViewProjection() const;

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns>ワールドトランスフォーム</returns>
	const WorldTransform& GetWorldTransform() const;

public: // メンバ関数ポインタの配列
	// 更新のテーブル
	static void (Camera::*updateTable[])();

private:                            // メンバ変数
	WorldTransform worldTransform_; // ワールド変換データ

	ViewProjection viewProjection_; // ビュープロジェクション

	// 追従対象
	const WorldTransform* target_ = nullptr;
};

using CameraMode = Camera::Mode;