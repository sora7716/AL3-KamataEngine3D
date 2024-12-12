#pragma once
#include "WorldTransform.h"
#include <vector>
#include <memory>

// 前方宣言
class Model;
class ViewProjection;

class TitleName {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ」
	/// </summary>
	TitleName() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleName() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private://メンバ関数
	/// <summary>
	/// アニメーション
	/// </summary>
	void Animation();

private: // メンバ変数
	float frame_ = 0;
	std::vector<Model*> models_;
	ViewProjection* viewProjection_ = nullptr;
	std::vector<WorldTransform*> worldTransforms_;
};
