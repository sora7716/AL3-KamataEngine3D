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

// タイトルシーンのモデル
void Create::TitleSceneModel() {
	titleNameModels_.resize((int)TitleNameType::kTitleNameNum);
	titleNameModels_[typeMa].reset(Model::CreateFromOBJ("ma", true)); // 魔
	titleNameModels_[typeJo].reset(Model::CreateFromOBJ("jo", true)); // 女
	titleNameModels_[typeNo].reset(Model::CreateFromOBJ("no", true)); // の
	titleNameModels_[typeSe].reset(Model::CreateFromOBJ("se", true)); // せ
	titleNameModels_[typeI].reset(Model::CreateFromOBJ("i", true));   // い
}

// ゲームシーンのモデル
void Create::GameSceneModel() {
	models_.resize((int)Type::kModelNum); // 配列の大きさを設定
	models_[typeHexagon].reset(Model::CreateFromOBJ("hexagon", true));
	models_[typeSkydome].reset(Model::CreateFromOBJ("skydome", true));
	models_[typeGround].reset(Model::CreateFromOBJ("ground", true));
	models_[typeParticle].reset(Model::CreateFromOBJ("particle", true));

	// プレイヤーのモデル
	playerModels_.resize((int)PlayerParts::kPlayerNum);                           // サイズを設定
	playerModels_[typeHead].reset(Model::CreateFromOBJ("float_Head", true));      // 頭
	playerModels_[typeBody].reset(Model::CreateFromOBJ("float_Body", true));      // 体
	playerModels_[typeRightArm].reset(Model::CreateFromOBJ("float_R_arm", true)); // 右腕
	playerModels_[typeLeftArm].reset(Model::CreateFromOBJ("float_L_arm", true));  // 左腕
	playerModels_[typeStaff].reset(Model::CreateFromOBJ("hammer", true));         // 杖

	// ミミックのモデル
	mimicModels_.resize((int)MimicParts::kPartsNum);                               // サイズの設定
	mimicModels_[typeBox].reset(Model::CreateFromOBJ("box", true));                // 箱
	mimicModels_[typePadlock].reset(Model::CreateFromOBJ("padlock", true));        // 南京錠
	mimicModels_[typeKeyHole].reset(Model::CreateFromOBJ("keyHole", true));        // 鍵穴
	mimicModels_[typeLid].reset(Model::CreateFromOBJ("lid", true));                // 蓋
	mimicModels_[typeEye].reset(Model::CreateFromOBJ("eye", true));                // 目
	mimicModels_[typeToothUp].reset(Model::CreateFromOBJ("upperTeeth", true));     // 上の歯
	mimicModels_[typeToothBottom].reset(Model::CreateFromOBJ("lowerTeeth", true)); // 下の歯
	mimicModels_[typeTongue].reset(Model::CreateFromOBJ("tongue", true));          // 舌
}

// エンドシーンのモデル
void Create::EndSceneModel() {}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(int subscript) const { return models_[subscript].get(); }

// プレイヤーのモデルのゲッター
std::vector<std::unique_ptr<Model>>& Create::GetPlayerModel() {
	// TODO: return ステートメントをここに挿入します
	return playerModels_;
}

// ミミックのモデルのゲッター
std::vector<std::unique_ptr<Model>>& Create::GetMimicModel() {
	// TODO: return ステートメントをここに挿入します
	return mimicModels_;
}

// タイトル名のモデルのゲッター
std::vector<std::unique_ptr<Model>>& Create::GetTitleNameModel() {
	// TODO: return ステートメントをここに挿入します
	return titleNameModels_;
}

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }

std::vector<uint32_t> Create::GetTextureHandle(){
	return textureHandle_;
}
