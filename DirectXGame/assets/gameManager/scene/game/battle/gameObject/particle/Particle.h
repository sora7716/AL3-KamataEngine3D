#pragma once
#include "ObjectColor.h"
#include "WorldTransform.h"
#include "assets/math/Math.h"
#include <vector>

// 前方宣言
class Model;
class ViewProjection;


/// <summary>
/// パーティクル
/// </summary>
class Particle {
private: // 構造体
	/// <summary>
	/// 球の構造体
	/// </summary>
	typedef struct Sphere {
		WorldTransform* worldTransform;
		ObjectColor objectColor;
		Vector4 color;
		float radius;
		float angle;
		float speed;
		float isAlive;
	} Sphere;

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Particle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Particle() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// デバックテキスト
	/// </summary>
	void DebugText();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ関数
	/// <summary>
	/// パーティクルを生成
	/// </summary>
	void ParticleCreate();

	/// <summary>
	/// パーティクルを動かす
	/// </summary>
	void ParticleMove();

	/// <summary>
	/// パーティクルの更新
	/// </summary>
	void ParticleUpdate();

	/// <summary>
	/// ブレンド
	/// </summary>
	/// <param name="particle">パーティクル</param>
	void Blend(Sphere &particle);

public: // 静的メンバ変数
	static inline const int kParticleNum = 500;
	static inline const float kParticleSize = 0.3f;

private: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform emission_;
	std::vector<Sphere> particles_;
	ObjectColor objectColor_ = {};
	Vector4 color_ = RED;
};
