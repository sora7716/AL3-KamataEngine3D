#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Player {
public://メンバ関数

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

  private: // メンバ変数
  WorldTransform worldTransform_;//ワールドトランスフォーム

  Model* model_ = nullptr;//3Dモデル

  uint32_t textureHandle_ = 0u;//プレイヤーのテクスチャ

  ViewProjection* viewProjection_ = nullptr;//ビュープロジェクション

};
