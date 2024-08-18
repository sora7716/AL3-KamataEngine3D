#include "Create.h"
#include "Model.h"
#include "TextureManager.h"
// コンストラクタ
Create::Create() {}

// デストラクタ
Create::~Create() {
	delete *models_; // 削除
	for (auto model : models_) {
		model = nullptr; // 箱も削除
	}
}

// モデルをクリエイト
void Create::ModelCreate() { 
	//プレイヤー
	models_[(int)playerType] = Model::Create();
}

// テクスチャをクリエイト
void Create::TextureCreate() { 
	//プレイヤー
	textureHandle_[(int)playerType] = TextureManager::Load("test/player.png"); 
}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
