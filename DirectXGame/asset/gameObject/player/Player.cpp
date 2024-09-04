#include "Player.h"
#include "Model.h"
#include "ViewProjection.h"
#include "cassert"

///初期化処理
void Player::Initialize(Model* model, ViewProjection* viewProjection) {

	///NULLポインタチェック
	assert(model);

	///メンバ変数に引数のデータを記録する
	model_ = model;
	viewProjection_ = viewProjection;

	///ワールドトランスフォームの初期化
	worldTransform_.Initialize();

}

///更新処理
void Player::Update() {

	///行列の更新
	worldTransform_.UpdateMatrix();

}

///描画処理
void Player::Draw() {

	///モデルの描画
	model_->Draw(worldTransform_, *viewProjection_);

}
