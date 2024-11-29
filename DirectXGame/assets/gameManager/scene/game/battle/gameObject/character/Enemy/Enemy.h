#pragma once
#include "Vector2.h"
#include "assets/gameManager/gameModel/create/mimicModel/MimicModel.h"
#include "assets/gameManager/scene/game/battle/gameObject/character/BaseCharacter.h"

//前方宣言
class Player;

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

private://メンバ関数

	/// <summary>
	/// 移動
	/// </summary>
	void Move();


public: // 静的メンバ変数
	/// <summary>
	/// プレイヤーのセッター
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player*player);

	static inline const float kSpeed = 1.0f;

private: // メンバ変数
	std::unique_ptr<MimicModel> mimicModel_ = nullptr;
	Vector2 circulaMoveRadius_ = {};
	Vector3 center = {};
	Vector3 velocity_ = {};

	//攻撃用の変数
	bool isAttacking = false;
	Player* player_ = nullptr;
	float yaw_; //横回転用
	float pitch_; //縦回転用

	/// <summary>
	/// 
	/// </summary>
	/// <param name="player"></param>
	/// <param name="enemy"></param>
	/// <returns></returns>
	float CalculateDistance(const Vector3& player, const Vector3& enemy);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="target"></param>
	void MoveToward(const Vector3& target);

	/// <summary>
	/// 
	/// </summary>
	void Idle();
};
