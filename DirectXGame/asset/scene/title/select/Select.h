#pragma once
#include "asset/math/Math.h"

// 前方宣言
class RailCamera;
class Player;

/// <summary>
/// セレクト画面
/// </summary>
class Select {
public:  // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Select()=default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Select() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="camera">カメラ</param>
	void Initialize(Player*player,RailCamera*camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(bool isMoveGameScene);

	/// <summary>
	/// ホームかどうかのフラグ
	/// </summary>
	/// <returns>isHome</returns>
	bool IsHome();

	/// <summary>
	/// セレクト画面への遷移フラグ
	/// <returns></returns>
	bool IsMoveSelect();

	/// <summary>
	/// フレームのゲッター
	/// </summary>
	/// <returns></returns>
	float GetFrame();

private:

	/// <summary>
	/// セレクト画面へ遷移
	/// </summary>
	void SelectScene();

public://静的メンバ変数

	static inline const float kEndFrame = 120.0f;//最大フレーム

private: // メンバ変数
	//カメラ
	RailCamera* camera_ = nullptr;
	//プレイヤー
	Player* player_ = nullptr;
	//セレクト画面に遷移フラグ
	bool isMoveSelect_ = false;
	//ゲームルール画面に遷移フラグ
	bool isMoveGemeRule_ = false;
	//ボタンを押したかどうかのフラグ
	bool isWasButtonPressed_ = false;
	//線形補間に使用するフレーム
	float frame_ = 0.0f;
	//元の画面にいるかどうか
	bool isHome_ = true;
};
