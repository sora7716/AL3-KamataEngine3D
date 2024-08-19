#pragma once

// 前方宣言
class Player;

/// <summary>
/// プレイヤーコマンドのインターフェース
/// </summary>
class IPlayerCommand {
public: // メンバ関数
	//純粋仮想関数
	virtual ~IPlayerCommand() = default;
	virtual void Exec(Player& player) = 0;
};
