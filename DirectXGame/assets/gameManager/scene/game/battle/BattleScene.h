#pragma once
// シーン
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameObject/Shape/hexagon/Hexagon.h"
#include "assets/gameObject/Shape/obb/OBB.h"

// ゲームモデル
#include "assets/failLoad/map/MapChipField.h"
#include "assets/gameObject/honeycomb/Honeycomb.h"

// ワイヤーフレーム
#include "assets/gameObject/shape/hexagon/Hexagon.h"
#include "assets/gameObject/shape/obb/OBB.h"

/// <summary>
/// バトルシーン
/// </summary>
class BattleScene : public IScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	BattleScene() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BattleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

private: // メンバ変数
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// OBB
	Shape::OBBMaterial obbMaterial_ = {};
	std::unique_ptr<OBB> obb_ = nullptr;

	// 六角形
	std::unique_ptr<Hexagon> hexagon_ = nullptr;
	Shape::HexagonMaterial hexagonMatrial_ = {};

	// ハニカム
	std::unique_ptr<Honeycomb> honeycomb_ = nullptr;

	// マップ
	std::unique_ptr<MapChipField> mapChipField_ = nullptr;
};
