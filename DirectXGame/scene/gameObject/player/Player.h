#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"

class Player {
public://メンバ関数

	/// <summary>
	/// 向きのenum
	/// </summary>
	enum class LRDirection {
		kRight,
		kLeft,
	};


  /// <summary>
  /// 初期化
  /// </summary>
  /// <param name="model">モデルクラス</param>
  /// <param name="textureHandle">テクスチャ</param>
  /// <param name="viewProjection">ビュープロジェクション</param>
  void Initialize(Model* model, const uint32_t &textureHandle, ViewProjection* viewProjection,const Vector3& position);

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

  /// <summary>
  /// プレイヤーの急ブレーキ
  /// </summary>
  void Brake(bool isBrake);

  /// <summary>
  /// プレイヤーの速度
  /// </summary>
  void Velocity(Vector3 acceleration);

  /// <summary>
  /// キー入力していないとの減速
  /// </summary>
  /// <returns>X方向の速度</returns>
  float Deceleration();

  /// <summary>
  /// プレイヤーの行動
  /// </summary>
  void Action();

  /// <summary>
  /// プレイヤーの向いている向き
  /// </summary>
  /// <param name="direction">向かせたい向き</param>
  void Direction(LRDirection direction);

  /// <summary>
  /// アングルとタイマーの記録
  /// </summary>
  void RecordAngleAndTime();

  /// <summary>
  /// 振り向きアニメーション
  /// </summary>
  float TurnAround(float* destinationRotationYTable);

  /// <summary>
  /// プレイヤーの向き
  /// </summary>
  void Angle();

  /// <summary>
  /// プレイヤーのブレーキと向く方向
  /// </summary>
  /// <param name="direction">向いてほしい向き</param>
  void Movement(LRDirection direction);

  /// <summary>
  /// プレイヤーが地上にいるときの行動
  /// </summary>
  void OnGround();

  /// <summary>
  /// 描画	
  /// </summary>
  void Draw();

private: // メンバ変数

  WorldTransform worldTransform_;//ワールドトランスフォーム

  Model* model_ = nullptr;//3Dモデル

  uint32_t textureHandle_ = 0u;//プレイヤーのテクスチャ

  ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション

  MyVector3 velocity_ = {};//プレイヤーの速度

  bool isBrake_ = false;//ブレーキしているかのフラグ

  LRDirection lrDirection_ = LRDirection::kRight;//プレイヤーの向き

  float turnFirstRotationY_ = 0.0f;//旋回開始時間の角度
  
  float turnTimer_ = 0.0f;//旋回タイマー

  bool onGround_ = true;

  private://静的メンバ変数

  static inline const float kTimeTurn = 0.3f;//旋回時間<秒>

  static inline const float kAcceleration = 0.01f;//加速度
  
  static inline const float kAttenuation = 0.01f;//減速
  
  static inline const float kLimitRunSpeed = 0.5f;//走る速さの上限

  static inline const float kGravityAcceleration = 0.8f;//重力加速度(下方向)

  static inline const float kLimitFallSpeed = 0.9f;//最大落下速度(下方向)

  static inline const float kJumpAcceleration = 2.0f;//ジャンプの初速度(上方向)
  
  static inline const float kAttenuationLading = 0.01f;//着地時の減衰
};
