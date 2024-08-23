#include "TimedCall.h"
#include "asset/gameObject/enemy/statePattern/IEnemyState.h"


// コンストラクタ
TimedCall::TimedCall(function<void(WorldTransform&)> enemyState, uint32_t time) : enemyState_(enemyState), time_(time){}

// 更新
void TimedCall::Update(WorldTransform &worldTransform) { 
	if (isFinished_) {
		return;//完了なら早期リターン
	}
	time_--;
	if (time_ <= 0) {
		isFinished_ = true;//完了フラグ
		enemyState_(worldTransform);//呼び出したい関数を呼び出し
	}
}

// 完了かどうかのゲッター
bool TimedCall::IsFinished() { return isFinished_; }
