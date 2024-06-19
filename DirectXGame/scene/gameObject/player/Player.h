#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Player {
public://メンバ関数

	// 左右
	enum class LRDirection {
		kLeft,
		kRight,
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
  const WorldTransform& GetWorldTransform();

  /// <summary>
  /// ベロシティのゲッター
  /// </summary>
  /// <returns></returns>
  const Vector3 GetVelocity();

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

  private://静的メンバ変数
  static inline const float kAcceleration   = 0.1f;//加速
  static inline const float kAttenuation    = 0.1f;//減速
  static inline const float kLimitRunSpeed  = 0.9f;//移動速度の上限
  static inline const float kTimeTurn      = 0.3f;//旋回時間<秒>
  static inline const float kGravityAcceleration = 0.9f;//重力加速度
  static inline const float kLimitFallSpeed = 1.0f;//最大落下速度
  static inline const float kJumpAcceleration = 4.0f;//ジャンプの初速

};
