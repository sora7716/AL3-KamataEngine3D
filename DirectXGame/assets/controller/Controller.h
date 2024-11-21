#pragma once

// 前方宣言
class Player;
class FollowCamera;
class Controller {
public: // 列挙型
	// 操作するやつ
	enum class ControlType { kGamepad, kKeyboard };

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Controller() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Controller() = default;

	/// <summary>
	/// 操作するやつを決める
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	/// <param name="controlType">操作タイプ</param>
	void ControlUpdate(Player* player, FollowCamera* followCamera, ControlType controlType = ControlType::kKeyboard);

private: // メンバ関数
	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	void Gamepad(Player* player, FollowCamera* followCamera);

	/// <summary>
	/// キーボードの操作
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	void Keyboard(Player* player, FollowCamera* followCamera);
};
