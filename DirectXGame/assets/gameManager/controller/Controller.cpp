#include "Controller.h"
#include "assets/gameManager/scene/game/battle/gameObject/camera/followCamera/FollowCamera.h"
#include "assets/gameManager/scene//game/battle/gameObject/character/player/Player.h"

//操作方法を管理する関数ポインタの配列
void (Controller::*Controller::ControllerTable[])() = {
    &Gamepad,
    &Keyboard,
};


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
	(this->*ControllerTable[(int)controlType])();
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
