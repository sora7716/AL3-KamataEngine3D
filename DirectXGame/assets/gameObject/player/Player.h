#pragma once
#include "PlayerParts.h"
#include "assets/create/Create.h"

#include "memory"
using namespace std;

class Player {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model"></param>
	/// <param name="viewProjection"></param>
	void Initialize(Create* create, ViewProjection* viewProjection);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	const WorldTransform& GetWorldPosition() { return this->worldTransform_; }

	/// <summary>
	/// パーツを作る
	/// </summary>
	void CreateParts();

	/// <summary>
	/// パーツの初期化
	/// </summary>
	void InitializeParts();



private:

	Create *create_ = nullptr;

	WorldTransform worldTransform_;

	ViewProjection* viewProjection_ = nullptr;

	unique_ptr<IPlayerParts> parts[IPlayerParts::PARTS_NUM] = {nullptr};

};
