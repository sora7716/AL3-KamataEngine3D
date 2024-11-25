#pragma once
//シーン
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameObject/obb/OBB.h"
#include "assets/gameObject/Hexagon/Hexagon.h"

//ゲームモデル
#include "assets/gameObject/honeycomb/Honeycomb.h"
#include "assets/failLoad/map/MapChipField.h"

//ワイヤーフレーム
#include "assets/gameObject/shape/obb/OBB.h"
#include "assets/gameObject/shape/hexagon/Hexagon.h"

/// <summary>
/// バトルシーン
/// </summary>
class BattleScene :public IScene{

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
	
	//OBB
	Shape::OBBMaterial obbMaterial_ = {};
	//六角形
	std::unique_ptr<Hexagon> hexagon_ = nullptr;
	Shape::HexagonMaterial hexagonMatrial_ = {};

	//ハニカム
	std::unique_ptr<Honeycomb> honeycomb_ = nullptr;

	//マップ
	std::unique_ptr<MapChipField> mapChipField_ = nullptr;


	WorldTransform worldTransform_;
	Vector3 worldPos_ = {};
	std::vector<FbxMesh*> mimicMeshs_;
};
