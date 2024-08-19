#pragma once
#include "Command.h"

// 前方宣言
class Input;

/// <summary>
/// コマンドを実行した結果を返すクラス
/// </summary>
class InputHandle {

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
	/// 初期化
	/// </summary>
	void Initialize(Input* input);

	/// <summary>
	/// 横移動のコマンドを実行
	/// </summary>
	/// <returns></returns>
	IPlayerCommand* PlayerBesideMoveInput();

	/// <summary>
	/// 縦の移動のコマンドを実行
	/// </summary>
	/// <returns></returns>
	IPlayerCommand* PlayerVerticalMoveInput();

	/// <summary>
	/// 回転をするコマンドを実行
	/// </summary>
	/// <returns></returns>
	IPlayerCommand* PlayerRotateInput();

	/// <summary>
	/// Leftを押したら
	/// </summary>
	void AssingMoveLeftCommand2PressKeysLeft();

	/// <summary>
	/// Rightを押したら
	/// </summary>
	void AssingMoveRightCommand2PressKeysRight();

	/// <summary>
	/// Downを押したら
	/// </summary>
	void AssingMoveDownCommand2PressKeysDown();

	/// <summary>
	/// Upを押したら
	/// </summary>
	void AssingMoveUpCommand2PressKeysUp();

	/// <summary>
	/// Dを押したら
	/// </summary>
	void AssingRotateRightCommand2PressKeyD();

	/// <summary>
	/// Aを押したら
	/// </summary>
	void AssingRotateLeftCommand2PressKeyA();

private:// メンバ変数

	Input* input_ = nullptr; // キー入力

	IPlayerCommand* pressKeyLeft_ = nullptr;  // 左
	IPlayerCommand* pressKeyRight_ = nullptr; // 右
	IPlayerCommand* pressKeyDown_ = nullptr;  // 下
	IPlayerCommand* pressKeyUp_ = nullptr;    // 上
	IPlayerCommand* pressKeyA_ = nullptr;     // A
	IPlayerCommand* pressKeyD_ = nullptr;     // D
};
