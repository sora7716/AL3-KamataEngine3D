#pragma once
#include "assets/math/collision/shape/Shape.h"

/// <summary>
/// サーチライト
/// </summary>
class Searchlight :public Shape{
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Searchlight() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Searchlight() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="serchlightMaterial">サーチライトの素材</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(const SerchlightMaterial&& serchlightMaterial ,ViewProjection*viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public://静的メンバ変数
	static inline const int kSubdivisions = 20;

private: // メンバ変数
	SerchlightMaterial serchlightMaterial_ = {};
	Vector3 beginPos_[kSubdivisions];
	Vector3 endPos_[kSubdivisions];
};
