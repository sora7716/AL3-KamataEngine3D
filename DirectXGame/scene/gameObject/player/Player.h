#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "calculate/collision/Collision.h"

// 前方宣言
class MapChipField;
class Enemy;

class Player {
public: // 構造体
	// 左右
	enum class LRDirection {
		kLeft,
		kRight,
	};

	typedef struct CollisionMapChipInfo {
		bool celling = false;
		bool landing = false;
		bool hitWallLeft = false;
		bool hitWallRight = false;
		Vector3 velocity = {};
	} CollisionMapChipInfo;

	// 角
	enum Corner {
		kRightBottom, // 右上
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner, // 要素数
	};

public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャ</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="position">ポジション</param>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(bool isFadeFinished);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ワールドトランスフォームのゲッター
	/// </summary>
	/// <returns></returns>
	WorldTransform& GetWorldTransform();

	/// <summary>
	/// ベロシティのゲッター
	/// </summary>
	/// <returns></returns>
	const Vector3 GetVelocity()const ;

	/// <summary>
	/// 向いている向きのゲッター
	/// </summary>
	/// <returns></returns>
	const LRDirection& GetLRDirection()const ;

	/// <summary>
	/// マップチップのセッター
	/// </summary>
	/// <param name="mapChipField"></param>
	void SetMapChipField(MapChipField* mapChipField);

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	/// <returns></returns>
	AABB GetAABB();

	/// <summary>
	/// 当たったら
	/// </summary>
	/// <param name="enemy"></param>
	bool OnCollision(const Enemy* enemy);

private: // メンバ関数
	/// <summary>
	/// 当たり判定をまとめる
	/// </summary>
	/// <param name="info"></param>
	void CollisionMapChip(CollisionMapChipInfo& info);

	/// <summary>
	/// 上の当たり判定
	/// </summary>
	/// <param name="info"></param>
	void MapChipTop(CollisionMapChipInfo& info);

	/// <summary>
	/// 下の当たり判定」
	/// </summary>
	/// <param name="info"></param>
	void MapChipBottom(CollisionMapChipInfo& info);

	/// <summary>
	/// 右の当たり判定
	/// </summary>
	/// <param name="info"></param>
	void MapChipRight(CollisionMapChipInfo& info);

	/// <summary>
	/// 左の当たり判定
	/// </summary>
	/// <param name="info"></param>
	void MapChipLeft(CollisionMapChipInfo& info);

	/// <summary>
	/// 動かす
	/// </summary>
	/// <param name="info"></param>
	void MoveMent(CollisionMapChipInfo& info);

	/// <summary>
	/// 当たっているのか
	/// </summary>
	/// <param name="info"></param>
	void IsCollisionTop(const CollisionMapChipInfo& info);

	/// <summary>
	/// 角のポジション
	/// </summary>
	/// <param name="center"></param>
	/// <param name="corner"></param>
	/// <returns></returns>
	Vector3 CornerPosition(const Vector3& center, Corner corner);

	/// <summary>
	/// 着地状態と空中状態の切り替え
	/// </summary>
	/// <param name="info"></param>
	void SwitchOnGround(CollisionMapChipInfo& info);

	/// <summary>
	/// 壁にあたったときの判定
	/// </summary>
	/// <param name="info"></param>
	void IsHitWall(const CollisionMapChipInfo& info);

private:                                                   // メンバ変数
	WorldTransform worldTransform_;                        // ワールドトランスフォーム
	Model* model_ = nullptr;                               // 3Dモデル
	uint32_t textureHandle_ = 0u;                          // プレイヤーのテクスチャ
	ViewProjection* viewProjection_ = nullptr;             // ビュープロジェクション
	Vector3 velocity_ = {};                                // 速度
	LRDirection lrDirection_ = LRDirection::kLeft;         // どちらを向いているのか
	float turnFirstRotationY_ = 0.0f;                      // 旋回開始時の角度
	float turnTimer_ = 0.0f;                               // 旋回開始タイマー
	bool onGround_ = true;                                 // 接地状態フラグ
	MapChipField* mapChipField_ = nullptr;                 // マップチップフィールド
private:                                                   // 静的メンバ変数
	static inline const float kAcceleration = 0.05f;       // 加速
	static inline const float kAttenuation = 0.2f;         // 減速
	static inline const float kLimitRunSpeed = 0.9f;       // 移動速度の上限
	static inline const float kTimeTurn = 0.3f;            // 旋回時間<秒>
	static inline const float kGravityAcceleration = 0.2f; // 重力加速度
	static inline const float kLimitFallSpeed = 0.8f;      // 最大落下速度
	static inline const float kJumpAcceleration = 2.0f;    // ジャンプの初速
	static inline const float Blanc = 0.1f;                // 微小な余白
	// キャラクターの当たり判定のサイズ
	static inline const float kWidth = 1.0f;//横幅
	static inline const float kHeight = 1.0f;//縦幅
	static inline const float kAttenuationLanding = 0.8f;
	static inline const float kAttenuationWall = 2.0f;
};
