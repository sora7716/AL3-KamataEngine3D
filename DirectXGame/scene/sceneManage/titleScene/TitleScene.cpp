#include "TitleScene.h"
#include "Input.h"
#include "TextureManager.h"

#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>;
//コンストラクタ
TitleScene::TitleScene() { 
	finished_ = false; 
}

//デストラクタ
TitleScene::~TitleScene() {
	delete titleFontModel_;
}

// 初期化
void TitleScene::Initialize() { 

	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	titleFontModel_ = Model::CreateFromOBJ("titleFont",true); 
	titleFontTextureHandle_ = TextureManager::Load("white1x1.png");
	titleFontWorldTransform_.Initialize();
	titleFontWorldTransform_.rotation_.x = -(std::numbers::pi_v<float> / 2.0f);
	viewProjection_.Initialize();
}

//更新
void TitleScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	titleFontWorldTransform_.rotation_.y += 0.01f;
	titleFontWorldTransform_.UpdateMatrix();
}

//描画
void TitleScene::Draw() { 

	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// フェーズ
	titleFontModel_->Draw(titleFontWorldTransform_, viewProjection_, titleFontTextureHandle_); 

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

//終了フラグのゲッター
bool TitleScene::IsFinished() const { return finished_; }

//終了フラグのセッター
void TitleScene::SetIsFinished(const bool& isFinished) { finished_ = isFinished; }
