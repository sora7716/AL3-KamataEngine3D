#include "TitleScene.h"
#include "Input.h"
#include "TextureManager.h"

#include <cmath>
#include <numbers>
#define pi_f std::numbers::pi_v<float>;

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// コンストラクタ
TitleScene::TitleScene() { finished_ = false; }

// デストラクタ
TitleScene::~TitleScene() {
	delete fade_; // フェードの削除
}

// 初期化
void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	create_ = make_unique<Create>(); // 生成
	create_->ModelCreate();          // モデルを生成

	viewProjection_.Initialize();
	fade_ = new Fade();                                // フェードの生成
	fade_->Initialize();                               // フェードの初期化
	fade_->FadeStart(Fade::Status::FadeIn, kFadeTime); // フェードイン初期化

	// タイトルフォント
	Create::ObjectType typeTitleFont = Create::Type::kTitleFont;
	titleFont_ = make_unique<TitleFont>();                                      // 生成
	titleFont_->Initialize(create_->GetModel(typeTitleFont), &viewProjection_); // 初期化

	// 敵
	Create::ObjectType typeEnemy = Create::Type::kEnemy;
	for (int i = 0; i < 2; i++) {
		enemy_[i] = make_unique<Enemy>();
	}
	enemy_[0]->TitleInitialize(create_->GetModel(typeEnemy), &viewProjection_, {-8, -3, -23}, {0,-6,0});
	enemy_[1]->TitleInitialize(create_->GetModel(typeEnemy), &viewProjection_, {8, -3, -23}, {0, 6, 0});

	//ゲームスタートボタン
	Create::ObjectType typePressSpacae = Create::Type::kPressSpace;
	pressSpace_ = make_unique<GameStart>();
	pressSpace_->Initiaize(create_->GetModel(typePressSpacae), &viewProjection_, create_->GetTextureHandle(typePressSpacae));
}

// 更新
void TitleScene::Update() {
	ChangePhaseUpdate();
#ifdef _DEBUG

#endif // _DEBUG
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

	// 敵
	for (int i = 0; i < 2; i++) {
		enemy_[i]->Draw();
	}

	// タイトルフォント
	titleFont_->Draw();

	//スペースボタン
	pressSpace_->Draw();

	// フェード
	fade_->Draw(commandList);

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

// 終了フラグのゲッター
bool TitleScene::IsFinished() const { return finished_; }

// 終了フラグのセッター
void TitleScene::SetIsFinished(const bool& isFinished) { finished_ = isFinished; }

// 更新処理のフェーズの変更
void TitleScene::ChangePhaseUpdate() {
	titleFont_->Update(); // タイトルフォント
	pressSpace_->Update();//スペースボタン
	for (int i = 0; i < 2; i++) {
		enemy_[i]->TitleUpdate(); // 敵
	}
	switch (phase_) {
	case Phase::kFadeIn:
		// フェードイン
		fade_->Update(); // フェードの更新処理
		// TitleFontUpdate();
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
		}

		break;
	case Phase::kMain:
		// メインの処理
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->FadeStart(Fade::Status::FadeOut, kFadeTime);
		}
		break;
	case Phase::kFadeOut:
		// フェードアウト
		fade_->Update();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
}