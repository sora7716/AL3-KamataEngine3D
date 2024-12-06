#pragma once
#include "ObjectColor.h"
#include "WorldTransform.h"
#include <vector>

// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// パーティクル
/// </summary>
class Particle {
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

public://静的メンバ変数
	static inline const int kParticleNum = 1;
	static inline const float kParticleSize = 0.3f;

private: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	WorldTransform emission_;
	std::vector<WorldTransform*> particle_;
	std::vector<float> speed_;
	ObjectColor objectColor_ = {};
	Vector4 color_ = RED;
};
