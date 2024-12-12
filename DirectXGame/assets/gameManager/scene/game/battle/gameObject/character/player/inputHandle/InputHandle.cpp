#include "InputHandle.h"
#include "input/Input.h"

// 移動コマンドの生成をまとめた配列
void (InputHandle::*InputHandle::AssignCommandTable[])() = {
    &MoveLeftPressKeyA,
	&MoveRightPressKeyD,
	&MoveFrontPressKeyW,
	&MoveBackPressKeyS, 
	&StopNotPressAandD,
	&StopNotPressWandS,
};

// 水平移動のコマンド
ICommand* InputHandle::HorizontalMoveCommand() {
	if (Input::GetInstance()->PushKey(DIK_A)) {
		return pressMoveKey_[(int)InputMoveKey::kA];
	} else if (Input::GetInstance()->PushKey(DIK_D)) {
		return pressMoveKey_[(int)InputMoveKey::kD];
	}
	return pressMoveKey_[(int)InputMoveKey::kNotPressedAandD];
}

// 垂直移動のコマンド
ICommand* InputHandle::VerticalMoveCommand() {
	if (Input::GetInstance()->PushKey(DIK_W)) {
		return pressMoveKey_[(int)InputMoveKey::kW];
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		return pressMoveKey_[(int)InputMoveKey::kS];
	}
	return pressMoveKey_[(int)InputMoveKey::kNotPressedWandS];
}

// Aの入力
void InputHandle::MoveLeftPressKeyA() {
	ICommand* command = new KeyboardLeft();
	pressMoveKey_[(int)InputMoveKey::kA] = command;
}

// Dの入力
void InputHandle::MoveRightPressKeyD() {
	ICommand* command = new KeyboardRight();
	pressMoveKey_[(int)InputMoveKey::kD] = command;
}

// Wの入力
void InputHandle::MoveFrontPressKeyW() {
	ICommand* command = new KeyboardFront();
	pressMoveKey_[(int)InputMoveKey::kW] = command;
}

// Sの入力
void InputHandle::MoveBackPressKeyS() {
	ICommand* command = new KeyboardBack();
	pressMoveKey_[(int)InputMoveKey::kS] = command;
}

// AかつDを押してないとき
void InputHandle::StopNotPressAandD() {
	ICommand* command = new KeyboardStopHorizontal();
	pressMoveKey_[(int)InputMoveKey::kNotPressedAandD] = command;
}

// WかつSを押してないとき
void InputHandle::StopNotPressWandS() {
	ICommand* command = new KeyboardStopVertical();
	pressMoveKey_[(int)InputMoveKey::kNotPressedWandS] = command;
}
