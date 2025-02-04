#pragma once
#include "assets/gameManager/scene/game/gameObject/environment/BaseEnvironment.h"
#include <vector>

/// <summary>
/// ハニカム
/// </summary>
class Honeycomb : public BaseEnvironment {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Honeycomb() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Honeycomb() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(ViewProjection* viewProjection, std::shared_ptr<Model>&& model) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

public: // 静的メンバ変数
	static inline const uint32_t kHorizontal = 10;
	static inline const uint32_t kVertical = 10;

private: // メンバ変数
	// ワールドトランスフォームの配列
	std::vector<std::vector<WorldTransform*>> worldTransforms_;
	Vector3 hexagonScale_ = {1.0f, 1.0f, 1.0f};//六角形のサイズ
};
