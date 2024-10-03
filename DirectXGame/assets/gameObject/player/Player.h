#pragma once
#include "PlayerParts.h"

#include "memory"
using namespace std;

class Player {

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
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private:

	Model* model_ = nullptr;

	WorldTransform worldTransform_;

	ViewProjection* viewProjection_ = nullptr;

	unique_ptr<IPlayerParts> parts[IPlayerParts::PARTS_NUM] = {nullptr};

};
