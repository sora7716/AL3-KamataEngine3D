#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

//前方宣言
class MapChipField;

class Player {
public://メンバ関数

	// 左右
	enum class LRDirection {
		kLeft,
		kRight,
	};

	typedef struct CollisionMapChipInfo {
		bool celling = false;
		bool landing = false;
		bool hitWall = false;
		Vector3 velocity;
	} CollisionMapChipInfo;

	//角
	enum Corner {
		kRightBottom,//右上
		kLeftBottom,//左下
		kRightTop,//右上
		kLeftTop ,//左上

		kNumCorner,//要素数
	};

  /// <summary>
  /// 初期化
  /// </summary>
  /// <param name="model">モデル</param>
  /// <param name="textureHandle">テクスチャ</param>
  /// <param name="viewProjection">ビュープロジェクション</param>
  /// <param name="position">ポジション</param>
  void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection,const Vector3&position);

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

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
  const Vector3 GetVelocity();

  /// <summary>
  /// 向いている向きのゲッター
  /// </summary>
  /// <returns></returns>
  const LRDirection& GetLRDirection();

  /// <summary>
  /// マップチップのセッター
  /// </summary>
  /// <param name="mapChipField"></param>
  void SetMapChipField(MapChipField* mapChipField);

  private://メンバ関数
  void CollisionMapChip(CollisionMapChipInfo& info);

  void MapChipTop(CollisionMapChipInfo& info);
  void MapChipBottom(CollisionMapChipInfo& info);
  void MapChipRight(CollisionMapChipInfo& info);
  void MapChipLeft(CollisionMapChipInfo& info);

  void CollisionMoveMent(CollisionMapChipInfo& info);
  void IsCollision(const CollisionMapChipInfo& info);

  Vector3 CornerPosition(const Vector3& center, Corner corner);
  private: // メンバ変数

  WorldTransform worldTransform_;//ワールドトランスフォーム
  Model* model_ = nullptr;//3Dモデル
  uint32_t textureHandle_ = 0u;//プレイヤーのテクスチャ
  ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション
  Vector3 velocity_ = {};//速度
  LRDirection lrDirection_ = LRDirection::kLeft;//どちらを向いているのか
  float turnFirstRotationY_ = 0.0f;//旋回開始時の角度
  float turnTimer_ = 0.0f;//旋回開始タイマー
  bool onGround_ = true;//接地状態フラグ
  MapChipField* mapChipField_;
  private://静的メンバ変数
  static inline const float kAcceleration   = 2.0f;//加速
  static inline const float kAttenuation    = 0.1f;//減速
  static inline const float kLimitRunSpeed  = 0.9f;//移動速度の上限
  static inline const float kTimeTurn      = 0.3f;//旋回時間<秒>
  static inline const float kGravityAcceleration = 0.9f;//重力加速度
  static inline const float kLimitFallSpeed = 1.0f;//最大落下速度
  static inline const float kJumpAcceleration = 2.0f;//ジャンプの初速
  //キャラクターの当たり判定のサイズ
  static inline const float kWidth  = 0.8f;
  static inline const float kHeight = 0.8f;
  static inline const float kAttenuationWall = 2.0f;
};
