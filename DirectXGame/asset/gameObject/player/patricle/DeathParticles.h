#pragma once
#include "IDeathParticle.h"

#pragma region 頭のデスパーティクル

class HeadDeathParticles : public IDeathParticle {

public://メンバ変数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection,const Vector3 &position) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// パーティクルが動く処理
	/// </summary>
	void Move() override;

	/// <summary>
	/// アルファ値が減算される処理
	/// </summary>
	void SubtractAlpha() override;

};

#pragma endregion 

//=============================================================================================================================

#pragma region 体のデスパーティクル

class BodyDeathParticles : public IDeathParticle {

public: // メンバ変数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// パーティクルが動く処理
	/// </summary>
	void Move() override;

	/// <summary>
	/// アルファ値が減算される処理
	/// </summary>
	void SubtractAlpha() override;
};

#pragma endregion