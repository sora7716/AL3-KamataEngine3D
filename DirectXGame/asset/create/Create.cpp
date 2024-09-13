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
	models_[(int)typePlayerHead] = Model::CreateFromOBJ("head",true);//頭
	models_[(int)typePlayerBody] = Model::CreateFromOBJ("body",true);//体
	models_[(int)typePlayerLeft_Arm] = Model::CreateFromOBJ("left_arm",true);//左腕
	models_[(int)typePlayerRight_Arm] = Model::CreateFromOBJ("right_arm", true);//右腕
	models_[(int)typePlayerLeft_Ear] = Model::CreateFromOBJ("left_ear", true);//左耳
	models_[(int)typePlayerRight_Ear] = Model::CreateFromOBJ("right_ear", true);//右耳
	//障害物
	models_[(int)typeEnemy] = Model::CreateFromOBJ("toge", true);
	//天球
	models_[(int)typeSkyDome] = Model::CreateFromOBJ("SkyEntyu", true);
	//デスパーティクル
	models_[(int)typeDeathParticles] = Model::CreateFromOBJ("deathParticles", true);
	//ワープポイント
	models_[(int)typeWarp] = Model::CreateFromOBJ("warp", true);
	//タイトルフォント
	models_[(int)typeTitleFont] = Model::CreateFromOBJ("title", true);
	//リザルト天球
	models_[(int)typeResultSkyDome] = Model::CreateFromOBJ("skydome", true);
	models_[(int)typeSceneText] = Model::CreateFromOBJ("pressSpace", true);
	//スタートの文字
	models_[(int)typeStart] = Model::CreateFromOBJ("start_moji", true);
	//ルールの文字
	models_[(int)typeRule] = Model::CreateFromOBJ("rule_moji", true);
	//ルールの背景
	models_[(int)typeButtonBack] = Model::CreateFromOBJ("rule_back", true);
	//セレクトする用のボタン
	models_[(int)typeSelectButton] = Model::Create();
	//セレクトキー(W)の背景
	models_[(int)typekeyW_Back] = Model::CreateFromOBJ("W_button",true);
	//セレクトキー(W)の文字
	models_[(int)typekeyW_Moji] = Model::CreateFromOBJ("W_moji", true);
	// セレクトキー(S)の背景
	models_[(int)typekeyS_Back] = Model::CreateFromOBJ("S_button", true);
	// セレクトキー(S)の文字
	models_[(int)typekeyS_Moji] = Model::CreateFromOBJ("S_moji", true);
	// セレクトキー(ESC)の背景
	models_[(int)typekeyESC_Back] = Model::CreateFromOBJ("Escape_back", true);
	// セレクトキー(ESC)の文字
	models_[(int)typekeyESC_Moji] = Model::CreateFromOBJ("Escape_moji", true);
}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// モデルのゲッター
Model* Create::GetModel(Create::Type subscript) const { return models_[(int)subscript]; }

// テクスチャのゲッター
uint32_t Create::GetTextureHandle(Create::Type subscript) const { return textureHandle_[(int)subscript]; }
