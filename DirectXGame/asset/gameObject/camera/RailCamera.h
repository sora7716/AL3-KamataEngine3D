#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "asset/math/Math.h"

/// <summary>
/// レールカメラ
/// </summary> 
class RailCamera {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	RailCamera() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RailCamera() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="matWorld">ワールド座標</param>
	/// <param name="radian">回転角[ラジアン]</param>
	/// <param name="viewProjection">もともとあったビュープロジェクション</param>
	void Initialize(const Matrix4x4& matWorld,const Vector3& radian,const ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// カメラの軌道
	/// </summary>
	void Draw();

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

	/// <summary>
	/// トランスレイションのセッター
	/// </summary>
	/// <param name="translation">セットしたいtranslation</param>
	void SetTranslation(Vector3 translation);

	/// <summary>
	/// ローテションのセッター
	/// </summary>
	/// <param name="rotation">セットしたいrotation</param>
	void SetRotation(Vector3 rotation);

private: // メンバ変数

	WorldTransform worldTransform_;  // ワールド変換データ

	ViewProjection viewProjection_; // ビュープロジェクション

	std::vector<Vector3> controlPoints_;//制御点
	//媒介変数
	float t_ = 0;

};
