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
	envModels_[(int)Env::kGround].reset(Model::CreateFromOBJ("hexagon", true));
}

// エンドシーンのモデル
void Create::EndSceneModel() {}

// テクスチャをクリエイト
void Create::TextureCreate() {}

// タイトル名のモデルのゲッター
std::vector<std::shared_ptr<Model>>& Create::GetEnvModel() {
	// TODO: return ステートメントをここに挿入します
	return envModels_;
}

//テクスチャのゲッター
std::vector<uint32_t> Create::GetTextureHandle() { return textureHandles_; }
