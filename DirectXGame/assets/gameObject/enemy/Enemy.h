#pragma once
#include "vector"
#include "assets/gameobject/BaseCharacter.h"
#include "assets/math/Math.h"

/// <summary>
/// 敵クラス
/// </summary>
class Enemy : public BaseCharacter ,Math{

public: // メンバ関数
	// 初期化処理
	void Initialize(std::vector<Model*> models, ViewProjection* viewProjection) override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

	// 衝突時の処理
	void OnCollision([[maybe_unused]] Collider* other) override;

	//中心座標の取得
	Vector3 GetCenterPosition() const override;

	//座標の取得
	Vector3 GetPosition();

private:

	//各ワールドトランスフォームの初期化
	void InitializeWorldTransform();

	//浮遊ギミックの初期化
	void InitializeFloatingGimmick();

	//移動処理
	void Move();

	//浮遊ギミックの更新(敵は浮遊したりしないが、槍を動かす)
	void UpdateMoveGimmick();

private: // メンバ変数

	// 速度
	Vector3 velocity_;

	float floatingParameter_;

};
