#pragma once

// 前方宣言
class Player;
class FollowCamera;
class Controller final {
public: // 列挙型
	// 操作するやつ
	enum class ControlType { kGamepad, kKeyboard };

public: // メンバ関数

	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Controller* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	void Initialize(Player* player, FollowCamera* followCamera);

	/// <summary>
	/// 操作するやつを決める
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	/// <param name="controlType">操作タイプ</param>
	void ControlUpdate(ControlType controlType = ControlType::kKeyboard);

	//コピーコンストラクタの禁止
	Controller(const Controller& controller) = delete;
	//代入演算子の禁止
	Controller& operator=(const Controller& controller) = delete;

private: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Controller() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Controller() = default;

	/// <summary>
	/// ゲームパッドの操作
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	void Gamepad();

	/// <summary>
	/// キーボードの操作
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="followCamera">追従カメラ</param>
	void Keyboard();

private: // メンバ変数
	Player* player_ = nullptr;
	FollowCamera* followCamera_ = nullptr;
	static void (Controller::*ControllerTable[])();//操作方法を格納する関数ポインタの配列
};
