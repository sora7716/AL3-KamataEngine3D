#pragma once
#include <functional>
#include "WorldTransform.h"
using namespace std;

//前方宣言
class IEnemyState;

/// <summary>
/// 時限発動
/// </summary>
class TimedCall {

public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="enemyState">エネミーのステート</param>
	/// <param name="time">残り時間</param>
	TimedCall(function<void(WorldTransform&)>enemyState, uint32_t time);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TimedCall() = default;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="worldTransform">ワールドトランスフォーム</param>
	void Update(WorldTransform& worldTransform);

	/// <summary>
	/// 完了かどうかのゲッター
	/// </summary>
	/// <returns></returns>
	bool IsFinished();

private: // メンバ変数

	// コールバック
	function<void(WorldTransform&)> enemyState_;

	//残り時間
	uint32_t time_;

	// 完了フラグ
	bool isFinished_ = false;
};
