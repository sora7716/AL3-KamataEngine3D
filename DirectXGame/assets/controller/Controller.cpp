#include "Controller.h"
#include "assets/gameObject/camera/followCamera/FollowCamera.h"
#include "assets/gameObject/character/player/Player.h"

// 操作するやつを決める
void Controller::ControlUpdate(Player* player, FollowCamera* followCamera, ControlType controlType) {
	if (controlType == ControlType::kGamepad) {
		Gamepad(player, followCamera); // ゲームパッドの操作
	} else {
		Keyboard(player, followCamera); // キーボードの操作
	}
}

// ゲームパッドの操作
void Controller::Gamepad(Player* player, FollowCamera* followCamera) {
	// 移動
	player->GamepadControl();
	// 視点
	followCamera->GamepadControl();
}

// キーボードの操作
void Controller::Keyboard(Player* player, FollowCamera* followCamera) {
	// 移動
	player->KeyboardControl();
	// 視点
	followCamera->KeyboardControl();
}
