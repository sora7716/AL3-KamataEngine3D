#pragma once
#include "Vector2.h"
#include "assets/gameManager/gameModel/create/mimicModel/MimicModel.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"

/// <summary>
/// ミミックのクラス
/// </summary>
class Mimic : public BaseCharacter {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Mimic() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Mimic() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="model">モデル</param>
	void Initialize(std::vector<std::unique_ptr<Model>>&& models, ViewProjection* viewProjection) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

public: // 静的メンバ変数
	static inline const float kSpeed = 1.0f;
private: // メンバ変数
	std::unique_ptr<MimicModel> mimicModel_ = nullptr;
	Vector2 circulaMoveRadius_ = {};
	Vector3 center = {};
	Vector3 velocity_ = {};
};
