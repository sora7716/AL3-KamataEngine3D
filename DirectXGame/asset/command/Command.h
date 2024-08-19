#pragma once
#include "ICommand.h"

/// <summary>
/// 左へ移動のコマンド
/// </summary>
class MoveLeftCommand : public IPlayerCommand {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MoveLeftCommand() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveLeftCommand() override = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player& player) override;
};

/// <summary>
/// 右へ移動のコマンド
/// </summary>
class MoveRightCommand : public IPlayerCommand {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MoveRightCommand() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveRightCommand() override = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player& player) override;
};


/// <summary>
/// 下へ移動のコマンド
/// </summary>
class MoveDownCommand : public IPlayerCommand {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MoveDownCommand() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveDownCommand() override = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player& player) override;
};

/// <summary>
/// 上へ移動のコマンド
/// </summary>
class MoveUpCommand : public IPlayerCommand {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MoveUpCommand() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveUpCommand() override = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player& player) override;
};

/// <summary>
/// 右へ旋回のコマンド
/// </summary>
class RotateRightCommand:public IPlayerCommand{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	RotateRightCommand() = default;
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~RotateRightCommand() = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player"></param>
	void Exec(Player& player) override;
};

/// <summary>
/// 左へ旋回のコマンド
/// </summary>
class RotateLeftCommand : public IPlayerCommand {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RotateLeftCommand() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RotateLeftCommand() = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player"></param>
	void Exec(Player& player) override;
};