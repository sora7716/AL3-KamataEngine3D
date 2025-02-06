#pragma once
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "assets/gameManager/math/collison/wireFrame/obb/OBB.h"
#include <cassert>
#include <memory>
#include <vector>

/// <summary>
/// ベースキャラクター
/// </summary>
class BaseCharacter {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BaseCharacter() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseCharacter() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="models">モデル</param>
	virtual void Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	const WorldTransform* GetWorldTransform();

protected: // メンバ変数
	ViewProjection* viewProjection_;
	WorldTransform worldTransform_;
	std::vector<std::shared_ptr<Model>> models_;
};
