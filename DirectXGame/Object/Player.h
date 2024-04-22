#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <assert.h>
class Player {
private://メンバ変数

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

public://メンバ関数
	
	
  void Initialize(Model*model,uint32_t textureHandle);


  void Update();


  void Draw();

};
