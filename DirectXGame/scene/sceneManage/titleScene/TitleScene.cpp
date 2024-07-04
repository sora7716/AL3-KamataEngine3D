#include "TitleScene.h"
#include "Input.h"

//コンストラクタ
TitleScene::TitleScene() { 
	finished_ = false; 
}

//デストラクタ
TitleScene::~TitleScene() {}

// 初期化
void TitleScene::Initialize() {}

//更新
void TitleScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
}

//描画
void TitleScene::Draw() {}

//終了フラグのゲッター
bool TitleScene::IsFinished() const { return finished_; }

//終了フラグのセッター
void TitleScene::SetIsFinished(const bool& isFinished) { finished_ = isFinished; }
