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
	//自弾
	models_[(int)typePlayerBullet] = Model::Create();
	//敵
	models_[(int)typeEnemy] = Model::CreateFromOBJ("enemy",true);
	//敵弾
	models_[(int)typeEnemyBullet] = Model::Create();
	//スカイドーム
	models_[(int)typeSkydome] = Model::CreateFromOBJ("skydome",true);
	//地面
	models_[(int)typeGround] = Model::CreateFromOBJ("ground", true);
	//タイトルフォント
	models_[(int)typeTitleFont] = Model::CreateFromOBJ("title", true);
}

// テクスチャをクリエイト
void Create::TextureCreate() { 
	//プレイヤー
	textureHandle_[(int)typePlayer] = TextureManager::Load("test/player.png"); 
}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
