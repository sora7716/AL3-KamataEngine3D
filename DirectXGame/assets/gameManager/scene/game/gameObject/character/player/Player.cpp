#include "Player.h"
#include "assets/gameManager/modelCreate/player/PlayerModel.h"

// 初期化
void Player::Initialize(ViewProjection* viewProjection, std::vector<std::shared_ptr<Model>>&& models) { 
	//ベースの初期化
	BaseCharacter::Initialize(viewProjection, std::move(models)); 
	//モデルの初期化
	playerModel_->Initialize(viewProjection_, std::move(models_));
}

// 更新
void Player::Update() { 
	//ベースの更新
	BaseCharacter::Update();
	//モデルの更新
	playerModel_->Update();
	//親子付け
	playerModel_->SetParent(&worldTransform_);
	// 移動量に速さを反映
	if (isMoving_) {
		move_ = Math::Normalize(move_) * speed_;
		Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
		move_ = Math::TransformNormal(move_, rotMat);
		// Y軸周りの角度(θy)
		goalAngle_ = atan2(move_.x, move_.z);
		// 移動
		worldTransform_.translation_ += move_;
	}
	worldTransform_.rotation_.y = Math::LerpShortAngle(worldTransform_.rotation_.y, goalAngle_, rotateFrame_);

	bool right = Input::GetInstance()->PushKey(DIK_D);
	bool left = Input::GetInstance()->PushKey(DIK_A);
	bool front = Input::GetInstance()->PushKey(DIK_W);
	bool back = Input::GetInstance()->PushKey(DIK_S);
	if (right || left || front || back) {
		isMoving_ = true; // 移動した
		// 左右移動
		if (right) {
			move_.x = 1.0f;
		} else if (left) {
			move_.x = -1.0f;
		} else {
			move_.x = 0.0f;
		}
		// 前後移動
		if (front) {
			move_.z = 1.0f;
		} else if (back) {
			move_.z = -1.0f;
		} else {
			move_.z = 0.0f;
		}
	} else {
		isMoving_ = false; // 移動をやめた
	}
}

// 描画
void Player::Draw() { playerModel_->Draw(); }

//プレイヤーモデルのセッター
void Player::SetPlayerModel(std::shared_ptr<PlayerModel>&& playerModel) { playerModel_ = playerModel.get(); }
