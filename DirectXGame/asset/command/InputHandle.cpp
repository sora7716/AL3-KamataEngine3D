#include "InputHandle.h"
#include "input/Input.h"

// 初期化
void InputHandle::Initialize(Input* input) { input_ = input; }

// 横移動のコマンドを実行
IPlayerCommand* InputHandle::PlayerBesideMoveInput() {
	if (input_->PushKey(DIK_A)) {
		return pressKeyLeft_;
	} else if (input_->PushKey(DIK_D)) {
		return pressKeyRight_;
	}
	return nullptr;
}

// 縦移動のコマンドを実行
IPlayerCommand* InputHandle::PlayerVerticalMoveInput() {
	if (input_->PushKey(DIK_S)) {
		return pressKeyDown_;
	} else if (input_->PushKey(DIK_W)) {
		return pressKeyUp_;
	}
	return nullptr;
}

IPlayerCommand* InputHandle::PlayerRotateInput() { 
	if (input_->PushKey(DIK_LEFT)) {
		return pressKeyD_;
	} else if (input_->PushKey(DIK_RIGHT)) {
		return pressKeyA_;
	}
	return nullptr;
}

// Leftを押したら
void InputHandle::AssingMoveLeftCommand2PressKeysLeft() {
	IPlayerCommand* command = new MoveLeftCommand();
	pressKeyLeft_ = command;
}

// Rightを押したら
void InputHandle::AssingMoveRightCommand2PressKeysRight() {
	IPlayerCommand* command = new MoveRightCommand();
	pressKeyRight_ = command;
}

// Downを押したら
void InputHandle::AssingMoveDownCommand2PressKeysDown() {
	IPlayerCommand* command = new MoveDownCommand();
	pressKeyDown_ = command;
}

// Upを押したら
void InputHandle::AssingMoveUpCommand2PressKeysUp() {
	IPlayerCommand* command = new MoveUpCommand();
	pressKeyUp_ = command;
}

//Dを押したら
void InputHandle::AssingRotateRightCommand2PressKeyD() { 
	IPlayerCommand* command = new RotateRightCommand();
	pressKeyD_ = command;
}

//Aを押したら
void InputHandle::AssingRotateLeftCommand2PressKeyA() {
	IPlayerCommand* command = new RotateLeftCommand();
	pressKeyA_ = command;
}
