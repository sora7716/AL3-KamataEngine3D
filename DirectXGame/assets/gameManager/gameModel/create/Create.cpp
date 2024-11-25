#include "Create.h"

// コンストラクタ
Create::Create() {}

// デストラクタ
Create::~Create() {
	// モデルの削除
	models_.clear(); // 配列ごと削除

	// モデルの削除
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
	models_[static_cast<int>(typeHexagon)].reset(Model::CreateFromOBJ("hexagon", true));
	models_[static_cast<int>(typeSkydome)].reset(Model::CreateFromOBJ("skydome", true));
	models_[static_cast<int>(typeGround)].reset(Model::CreateFromOBJ("ground", true));

	// プレイヤーのモデル
	playerModels_.resize(PLAYER_MODEL_NUM);// サイズを設定
	playerModels_[typeHead].reset(Model::CreateFromOBJ("float_Head", true));      // 頭
	playerModels_[typeBody].reset(Model::CreateFromOBJ("float_Body", true));      // 体
	playerModels_[typeRightArm].reset(Model::CreateFromOBJ("float_R_arm", true)); // 右腕
	playerModels_[typeLeftArm].reset(Model::CreateFromOBJ("float_L_arm", true));  // 左腕
}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript].get(); }

// プレイヤーのモデルのゲッター
std::vector<std::unique_ptr<Model>>& Create::GetPlayerModel() {
	// TODO: return ステートメントをここに挿入します
	return playerModels_;
}

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
