#include "Controller.h"
#include "assets/gameObject/camera/followCamera/FollowCamera.h"
#include "assets/gameObject/character/player/Player.h"

//インスタンスのゲッター
Controller* Controller::GetInstance() { 
	static Controller instance;
	return &instance; 
}

// 初期化
void Controller::Initialize(Player* player, FollowCamera* followCamera) { 
	player_ = player;
	followCamera_ = followCamera;
}

// 操作するやつを決める
void Controller::ControlUpdate(ControlType controlType) {
	if (controlType == ControlType::kGamepad) {
		Gamepad(); // ゲームパッドの操作
	} else {
		Keyboard(); // キーボードの操作
	}
}

// ゲームパッドの操作
void Controller::Gamepad() {
	// 移動
	player_->GamepadControl();
	// 視点
	followCamera_->GamepadControl();
}

// キーボードの操作
void Controller::Keyboard() {
	// 移動
	player_->KeyboardControl();
	// 視点
	followCamera_->KeyboardControl();
}
