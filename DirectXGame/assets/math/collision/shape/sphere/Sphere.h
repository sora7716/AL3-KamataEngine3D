#pragma once
#include "assets/math/collision/shape/Shape.h"

class Sphere : public Shape {

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sphere() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sphere() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="sphere">スフィアの素材{positon,radius,color}</param>
	void Initialize(const SphereMaterial&& sphereMaterial,ViewProjection* viewProjection);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

#ifdef _DEBUG
	/// <summary>
	/// デバックテキスト
	/// </summary>
	/// <param name="label">名前</param>
	void DebugText(const char* label = "sphere");
#endif

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// カラーのセッター
	/// </summary>
	/// <param name="color"></param>
	void SetColor(Vector4 color);

	/// <summary>
	/// スフィアの素材のゲッター
	/// </summary>
	/// <returns></returns>
	SphereMaterial GetSphereMaterial() const;

	/// <summary>
	/// 球の素材のセッター
	/// </summary>
	/// <param name="material">球の素材</param>
	void SetSphere(const SphereMaterial& material);

private:                        // メンバ変数
	SphereMaterial sphere_{};     // スフィアの素材
	Vector3 screenA_{};           // スクリーン座標
	Vector3 screenB_{};           // スクリーン座標
	Vector3 screenC_{};           // スクリーン座標
};
