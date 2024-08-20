#pragma once
#include "WorldTransform.h"
// 前方宣言
class Model;
class ViewProjection;

/// <summary>
/// 敵のクラス
/// </summary>
class Enemy {

public://列挙型や構造体

	enum class Phase {
		Approach, //接近する
		Leave,    //離脱する
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="texture">テクスチャハンドル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, ViewProjection* viewProjection, const uint32_t& texture, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private://メンバ関数

	/// <summary>
	/// 接近中の更新
	/// </summary>
	void ApproachUpdate();

	/// <summary>
	/// 離脱中の更新
	/// </summary>
	void LeaveUpdate();

public: // 静的メンバ変数

	static inline const float kCharacterSpeed = 0.2f; //敵の進むスピード

private: // メンバ変数

	Model* model_ = nullptr;                   // モデル
	ViewProjection* viewProjection_ = nullptr; // ビュープロジェクション
	WorldTransform worldTransform_;            // ワールドトランスフォーム
	uint32_t texture_ = 0u;                    // テクスチャハンドル
	Phase phase_ = Phase::Approach;            //フェーズ 

private: //メンバ関数ポインタ

	/// <summary>
	/// エネミーの行動パターン
	/// </summary>
	static void (Enemy::*EnemyPhaseTable[])();
};
