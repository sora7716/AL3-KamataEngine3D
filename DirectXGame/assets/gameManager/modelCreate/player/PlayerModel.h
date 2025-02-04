#pragma once
#include "PlayerParts.h"
#include <array>
#include <memory>
#include <vector>
/// <summary>
/// プレイヤーモデル
/// </summary>
class PlayerModel {
public: // 列挙型
	enum class Parts { kBody, kFace, kEyeBrows, kHair, kLeftArm, kRightArm, kLeftThigh, kLeftLeg, kRightThigh, kRightLeg, kUpperCloth, kLowerCloth, kPartsNum };

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerModel() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerModel() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="models">モデル</param>
	void Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 親のセッター
	/// </summary>
	/// <param name="parent">親</param>
	void SetParent(const WorldTransform* parent);

private: // メンバ変数
	std::array<std::shared_ptr<PlayerParts>, (int)Parts::kPartsNum> parts = {nullptr};
};