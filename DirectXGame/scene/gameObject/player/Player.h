#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Player {
private://メンバ変数

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;


public://メンバ関数
	
  /// <summary>
  /// コンストラクター
  /// </summary>
	Player();

  /// <summary>
  /// デストラクター
  /// </summary>
	~Player();

  /// <summary>
  /// 初期化
  /// </summary>
  /// <param name="model">モデルクラス</param>
  /// <param name="textureHandle">テクスチャ</param>
  /// <param name="viewProjection">ビュープロジェクション</param>
  void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

  /// <summary>
  /// 更新処理
  /// </summary>
  void Update();

  /// <summary>
  /// 描画	
  /// </summary>
  void Draw();

};
