#pragma once
#include "assets/gameManager/scene/IScene.h"
#include "assets/gameObject/obb/OBB.h"
#include "assets/gameObject/Hexagon/Hexagon.h"

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
	std::unique_ptr<OBB> obb_ = nullptr;
	Math::OBBMaterial obbMaterial_ = {};

	//六角形
	std::unique_ptr<Hexagon> hexagon_ = nullptr;

	WorldTransform worldTransform_;
	Vector3 worldPos_ = {};
};
