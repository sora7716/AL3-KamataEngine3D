#pragma once
#include "PlayerParts.h"
#include "assets/create/Create.h"

#include "memory"
using namespace std;

class Input;

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

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* viewProjection) { viewProjection_ = viewProjection;}

private:

#pragma region このクラスのみで使うメンバ関数の宣言

	/// <summary>
	/// パーツを作る
	/// </summary>
	void CreateParts();

	/// <summary>
	/// パーツの初期化
	/// </summary>
	void InitializeParts();

	/// <summary>
	/// ジョイスティックによるプレイヤーの移動
	/// </summary>
	void JoyStickMove();

#pragma endregion

private:

	Create *create_ = nullptr;

	WorldTransform worldTransform_;

	const ViewProjection* viewProjection_ = nullptr;

	Input* input_ = nullptr;

	Vector3 velocity_ = {};
	Vector3 targetRotate_ = {};

	unique_ptr<IPlayerParts> parts[IPlayerParts::PARTS_NUM] = {nullptr};

	

};
