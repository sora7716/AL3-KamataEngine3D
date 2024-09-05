#include "Create.h"
#include "Model.h"
#include "TextureManager.h"
// コンストラクタ
Create::Create() {}

// デストラクタ
Create::~Create() {
	// モデルの削除
	for (auto model : models_) {
		delete model;
	}
	models_.clear();//配列ごと削除
}

// モデルをクリエイト
void Create::ModelCreate() {
	models_.resize(MODEL_NUM);//配列の大きさを設定
	// プレイヤー
	models_[(int)typePlayerHead] = Model::CreateFromOBJ("head",true);
	models_[(int)typePlayerBody] = Model::CreateFromOBJ("body",true);
	models_[(int)typePlayerLeft_Arm] = Model::CreateFromOBJ("left_arm",true);
	models_[(int)typePlayerRight_Arm] = Model::CreateFromOBJ("right_arm", true);
	//障害物
	models_[(int)typeEnemy] = Model::CreateFromOBJ("enemy", true);
	//天球
	models_[(int)typeSkyDome] = Model::CreateFromOBJ("SkyEntyu", true);
}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
