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
	models_.resize(MODEL_NUM); // 配列の大きさを設定

	models_[(int)ObjectType::kPlayerBody] = Model::CreateFromOBJ("Body", true);                  // 体
	models_[(int)ObjectType::kPlayerHead] = Model::CreateFromOBJ("Head", true);                  // 頭
	models_[(int)ObjectType::kPlayerLeft_UpperArm] = Model::CreateFromOBJ("LeftUpperArm", true); // 左上腕
	models_[(int)ObjectType::kPlayerLeft_LowerArm] = Model::CreateFromOBJ("LeftLowerArm", true); // 左腕
	models_[(int)ObjectType::kPlayerLeft_Thigh] = Model::CreateFromOBJ("LeftThigh", true);       // 左もも
	models_[(int)ObjectType::kPlayerLeft_Leg] = Model::CreateFromOBJ("LeftLeg", true);           // 左足
}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
