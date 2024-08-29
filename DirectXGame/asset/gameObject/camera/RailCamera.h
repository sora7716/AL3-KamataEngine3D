#pragma once
#include "WorldTransform.h"

//前方宣言
class ViewProjection;

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
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private: // メンバ変数

	WorldTransform worldTransform_;  // ワールド変換データ

	ViewProjection* viewProjection_; // ビュープロジェクション

};
