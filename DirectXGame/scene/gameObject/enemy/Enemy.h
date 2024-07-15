#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "calculate/collision/Collision.h"

//前方宣言
class MapChipField;
class Player;

class Enemy {

public:
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

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="texture">テクスチャ</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="position">今いるポジション</param>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(bool isFadeFinished);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// マップチップのセッター
	/// </summary>
	/// <param name="mapChipField"></param>
	void SetMapChipField(MapChipField* mapChipField);

	/// <summary>
	/// ワールド座標のゲッター
	/// </summary>
	/// <returns>ワールド座標</returns>
	Vector3 GetMatWorldPosition();

	/// <summary>
	/// AABBのゲッター
	/// </summary>
	/// <returns></returns>
	AABB GetAABB();

	/// <summary>
	/// 当たったら
	/// </summary>
	/// <param name="enemy"></param>
	void OnCollision(const Player* player);

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
	/// 壁に当たった場合
	/// </summary>
	/// <param name="info"></param>
	void IsHitWall(const CollisionMapChipInfo& info);

private:                             // メンバ変数
	Model* model_;                   // モデル
	ViewProjection* viewProjection_; // ビュープロジェクション
	uint32_t textureHandle_;         // テクスチャ
	WorldTransform worldTransform_;  // ワールドトランスフォーム
	Vector3 velocity_;               // 速度
	MapChipField* mapChipField_;     // マップチップフィールド
	bool onGround_;                  // 地上にいるかどうかのフラグ
	float walkTimer_;//経過時間

private:// 静的メンバ変数
	static inline const float kWalkSpeed = 0.2f;           // 歩行の速さ
	static inline const float kGravityAcceleration = 0.2f; // 重力加速度
	static inline const float kLimitFallSpeed = 0.8f;      // 最大落下速度
	static inline const float kAttenuation = 0.2f;         // 減速
	static inline const float Blanc = 0.8f;                // 微小な余白
	// キャラクターの当たり判定のサイズ
	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;
	static inline const float kAttenuationLanding = 0.9f;
	static inline const float kAttenuationWall = 2.0f;
	// アニメーション
	static inline const float kWalkMotionAngleStart = -45.0f; // 最初の角度(度数法)
	static inline const float kWalkMotionAngleEnd = 90.0f; // 最後の角度(度数法)
	static inline const float kWalkMotionTime = 1.0f;      // アニメーションの周期となるタイマー
};
