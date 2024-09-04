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
	models_[(int)typePlayer] = Model::CreateFromOBJ("head",true);
}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
