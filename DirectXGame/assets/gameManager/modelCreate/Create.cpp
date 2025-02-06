#include "Create.h"

// コンストラクタ
Create::Create() {}

// デストラクタ
Create::~Create() {
	// モデルの削除
	envModels_.clear(); // 配列ごと削除
}

// インスタンスのゲッター
Create* Create::GetInstance() {
	// 関数内にstatic変数として宣言
	static Create instance;
	return &instance;
}

// タイトルシーンのモデル
void Create::TitleSceneModel() {

}

// ゲームシーンのモデル
void Create::GameSceneModel() { 
	envModels_.resize((int)Env::kEnvNum);
	envModels_[(int)Env::kSkaydome].reset(Model::CreateFromOBJ("skydome", true));
	envModels_[(int)Env::kGround].reset(Model::CreateFromOBJ("hexagon", true));
	playerModels_.resize((int)PlayerParts::kPartsNum);
	playerModels_[(int)PlayerParts::kBody].reset(Model::CreateFromOBJ("body", true));
	playerModels_[(int)PlayerParts::kFace].reset(Model::CreateFromOBJ("face", true));
	playerModels_[(int)PlayerParts::kEyeBrows].reset(Model::CreateFromOBJ("eyeBrows", true));
	playerModels_[(int)PlayerParts::kHair].reset(Model::CreateFromOBJ("hair", true));
	playerModels_[(int)PlayerParts::kLeftArm].reset(Model::CreateFromOBJ("leftArm", true));
	playerModels_[(int)PlayerParts::kRightArm].reset(Model::CreateFromOBJ("rightArm", true));
	playerModels_[(int)PlayerParts::kLeftThigh].reset(Model::CreateFromOBJ("leftThigh", true));
	playerModels_[(int)PlayerParts::kLeftLeg].reset(Model::CreateFromOBJ("leftLeg", true));
	playerModels_[(int)PlayerParts::kRightThigh].reset(Model::CreateFromOBJ("rightThigh", true));
	playerModels_[(int)PlayerParts::kRightLeg].reset(Model::CreateFromOBJ("rightLeg", true));
	playerModels_[(int)PlayerParts::kUpperCloth].reset(Model::CreateFromOBJ("upperClothing", true));
	playerModels_[(int)PlayerParts::kLowerCloth].reset(Model::CreateFromOBJ("lowerClothing", true));
}

// エンドシーンのモデル
void Create::EndSceneModel() {}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// 環境モデルのゲッター
std::vector<std::shared_ptr<Model>>& Create::GetEnvModel() {
	// TODO: return ステートメントをここに挿入します
	return envModels_;
}

// プレイヤーモデルのゲッター
std::vector<std::shared_ptr<Model>>& Create::GetPlayerModel() {
	// TODO: return ステートメントをここに挿入します
	return playerModels_;
}


//テクスチャのゲッター
std::vector<uint32_t> Create::GetTextureHandle() { return textureHandles_; }
