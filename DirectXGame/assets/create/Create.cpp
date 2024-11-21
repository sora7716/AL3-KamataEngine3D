#include "Create.h"

// コンストラクタ
Create::Create() {}

// デストラクタ
Create::~Create() {
	// モデルの削除
	for (auto model : models_) {
		delete model;
	}
	models_.clear(); // 配列ごと削除

	// モデルの削除
	for (auto model : playerModels_) {
		delete model;
	}
	playerModels_.clear(); // 配列ごと削除
}

// インスタンスのゲッター
Create* Create::GetInstance() {
	// 関数内にstatic変数として宣言
	static Create instance;
	return &instance;
}

// モデルをクリエイト
void Create::ModelCreate() {
	models_.resize(MODEL_NUM); // 配列の大きさを設定
	playerModels_.resize(PLAYER_MODEL_NUM); // 配列の大きさを設定
	models_[static_cast<int>(typeHexagon)] = Model::CreateFromOBJ("hexagon", true);
	models_[static_cast<int>(typeSkydome)] = Model::CreateFromOBJ("skydome", true);
	models_[static_cast<int>(typeGround)] = Model::CreateFromOBJ("ground", true);

	playerModels_[static_cast<int>(typeHead)] = Model::CreateFromOBJ("float_Head", true);
}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// プレイヤーのモデルのゲッター
Model* Create::GetPlayerModel(Create::PlayerType subscript) const { return playerModels_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
