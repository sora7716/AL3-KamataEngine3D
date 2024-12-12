#pragma once
#include "assets/gameManager/scene/game/battle/gameObject/character/player/command/Command.h"
#include <array>

/// <summary>
/// インプットハンドル
/// </summary>
class InputHandle {
private: // 列挙型
	// 移動方向
	enum class InputMoveKey { kA, kD, kW, kS, kNotPressedAandD, kNotPressedWandS, kInputMoveKeyNum };

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	InputHandle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~InputHandle() = default;

	/// <summary>
	/// 水平移動のコマンド
	/// </summary>
	/// <returns></returns>
	ICommand* HorizontalMoveCommand();

	/// <summary>
	/// 垂直移動のコマンド
	/// </summary>
	/// <returns></returns>
	ICommand* VerticalMoveCommand();

private://メンバ関数
	/// <summary>
	/// Aの入力
	/// </summary>
	void MoveLeftPressKeyA();

	/// <summary>
	/// Dの入力
	/// </summary>
	void MoveRightPressKeyD();

	/// <summary>
	/// Wの入力
	/// </summary>
	void MoveFrontPressKeyW();

	/// <summary>
	/// Sの入力
	/// </summary>
	void MoveBackPressKeyS();

	/// <summary>
	/// AかつDを押してないとき
	/// </summary>
	void StopNotPressAandD();

	/// <summary>
	/// WかつSを押してないとき
	/// </summary>
	void StopNotPressWandS();

public://メンバ関数ポインタ
	//移動コマンドの生成をまとめた配列
	static void(InputHandle::*AssignCommandTable[])();

private: // メンバ変数
	// 移動のキー
	std::array<ICommand*, (int)InputMoveKey::kInputMoveKeyNum> pressMoveKey_;
};
