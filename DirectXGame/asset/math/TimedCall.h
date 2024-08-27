#pragma once
#include <functional>
using namespace std;

/// <summary>
/// 時限発動
/// </summary>
class TimedCall {

public: // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="fire">Fire関数</param>
	/// <param name="time">残り時間</param>
	/// <param name="enemy">敵</param>
	TimedCall(function<void()> fire, uint32_t time);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TimedCall() = default;

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 完了フラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool IsFinished();

	/// <summary>
	/// 残り時間のゲッター
	/// </summary>
	/// <returns></returns>
	uint32_t GetTimer();

private: // メンバ変数

	function<void()> fire_;   // コールバック
	uint32_t time_;                // 残り時間
	bool isFinished_ = false;      // 完了フラグ

};
