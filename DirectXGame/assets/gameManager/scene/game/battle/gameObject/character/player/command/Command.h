#pragma once

//前方宣言
class Player;

/// <summary>
/// コマンドのインターフェース
/// </summary>
class ICommand {
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ICommand() = default;

	//純粋仮想関数
	virtual ~ICommand() = default;

	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	virtual void Exec(Player* player) = 0;
};

/// <summary>
/// 左に動く
/// </summary>
class KeyboardLeft :public ICommand{
public://メンバ関数
	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player* player) override;
};

/// <summary>
/// 右に動く
/// </summary>
class KeyboardRight : public ICommand {
public: // メンバ関数
	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player* player) override;
};

/// <summary>
/// 前に動く
/// </summary>
class KeyboardFront : public ICommand {
public: // メンバ関数
	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player* player) override;
};

/// <summary>
/// 後ろに動く
/// </summary>
class KeyboardBack : public ICommand {
public: // メンバ関数
	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player* player) override;
};

/// <summary>
/// 水平移動を止める
/// </summary>
class KeyboardStopHorizontal : public ICommand {
public://メンバ関数
	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player* player) override;
};

/// <summary>
/// 垂直移動を止める
/// </summary>
class KeyboardStopVertical : public ICommand {
public://メンバ関数
	/// <summary>
	/// 実行
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void Exec(Player* player) override;
};