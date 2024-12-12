#include "TitleScene.h"

// デストラクタ
TitleScene::~TitleScene() {}

// 初期化
void TitleScene::Initialize(Create* create) {
	// 初期化
	IScene::Initialize(create);
}

	//textureHandle_ = TextureManager::Load("uvChecker.png");

	model_[0].reset(Model::CreateFromOBJ("ma", true));
	model_[1].reset(Model::CreateFromOBJ("jo", true));
	model_[2].reset(Model::CreateFromOBJ("no", true));
	model_[3].reset(Model::CreateFromOBJ("se", true));
	model_[4].reset(Model::CreateFromOBJ("i", true));

	for (int i = 0; i < 5; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {2.0f, 2.0f, 2.0f};
		worldTransform_[i].rotation_.y = pi_f / 2;
		const float position[5] = {-5.0f, -2.5f, 0.0f, 2.5f, 5.0f};
		worldTransform_[i].translation_ = {position[i], 8.0f, -32.0f};
	}
}

// 更新
void TitleScene::Update() {
	//更新
	IScene::Update();

	for (int i = 0; i < 5; i++) {

		// スケール
		std::string debugLabel = "scale" + std::to_string(i);
		ImGui::DragFloat3(debugLabel.c_str(), &worldTransform_[i].scale_.x, 0.01f);

		// 回転のデバッグテキスト
		debugLabel = "rotation" + std::to_string(i);
		ImGui::DragFloat3(debugLabel.c_str(), &worldTransform_[i].rotation_.x, 0.01f);

		// 座標のデバッグテキスト
		debugLabel = "translation" + std::to_string(i);
		ImGui::DragFloat3(debugLabel.c_str(), &worldTransform_[i].translation_.x ,0.01f);

		// 行列の更新
		worldTransform_[i].UpdateMatrix();
	}

	Animation();

	// デバックカメラの更新
	//DebugCameraMove();

	// カメラの更新
	railCamera_->Update();
}

// 描画
void TitleScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	//
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
	
	model_[0]->Draw(worldTransform_[0], viewProjection_);
	model_[1]->Draw(worldTransform_[1], viewProjection_);
	model_[2]->Draw(worldTransform_[2], viewProjection_);
	model_[3]->Draw(worldTransform_[3], viewProjection_);
	model_[4]->Draw(worldTransform_[4], viewProjection_);

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

void TitleScene::Animation() {

	static float frame = 0;
	static float endFrame = 200;

	if (frame <= endFrame) {
		frame++;
	}

	for (auto& worldTransform : worldTransform_) {
		const float begin = worldTransform.translation_.y;
		const float end = 2.0f;

		worldTransform.translation_.y = Math::Lerp(begin, end, Easing::GetInstance()->InOutExpo(frame / endFrame));
	}
}
