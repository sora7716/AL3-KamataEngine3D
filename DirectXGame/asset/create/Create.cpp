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
	models_[(int)typePlayer] = Model::Create();
	//敵
	models_[(int)typeEnemy] = Model::Create();

	models_[(int)typeSkydome] = Model::CreateFromOBJ("skydome",true);
}

// テクスチャをクリエイト
void Create::TextureCreate() { 
	//プレイヤー
	textureHandle_[(int)typePlayer] = TextureManager::Load("test/player.png"); 
	//敵
	textureHandle_[(int)typeEnemy] = TextureManager::Load("test/enemy.png");
}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
