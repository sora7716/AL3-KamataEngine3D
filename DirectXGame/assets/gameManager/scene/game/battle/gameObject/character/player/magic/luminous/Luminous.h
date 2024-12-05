#pragma once
#include "WorldTransform.h"
#include <vector>
// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// 光り輝く魔法
/// </summary>
class Luminous {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Luminous() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Luminous() = default;

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

	/// <summary>
	/// 飛んでいく方向のビュープロジェクションのセッター
	/// </summary>
	/// <param name="viewProjection"></param>
	void SetDirectionView(ViewProjection* viewProjection);

private: // メンバ関数
	/// <summary>
	/// エフェクト
	/// </summary>
	void Effect();

public: // 静的メンバ変数
	static inline const float kSpeed = 0.3f;
	static inline const float kSize = 0.3f;

private: // メンバ変数
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	std::vector<WorldTransform*> worldTransforms_;
	// 飛んでいく方向
	ViewProjection* directionViewProjection_ = nullptr;
	Vector3 move_ = {};
	bool isMoving_ = false;

	float theta_[2] = {};
};
