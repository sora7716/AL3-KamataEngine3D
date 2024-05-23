#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
class Player {
public://メンバ関数

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
  /// 描画	
  /// </summary>
  void Draw();

private: // メンバ変数

  WorldTransform worldTransform_;//ワールドトランスフォーム

  Model* model_ = nullptr;//3Dモデル

  uint32_t textureHandle_ = 0u;//プレイヤーのテクスチャ

  ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション

  MyVector3 velocity_ = {};//プレイヤーの速度

  static inline const float kAttenuation = 0.01f;
};
