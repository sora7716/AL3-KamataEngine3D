#include "TimedCall.h"

// コンストラクタ
TimedCall::TimedCall(function<void()> fire, uint32_t time) : fire_(fire), time_(time){}

// 更新
void TimedCall::Update() {
	if (isFinished_) {
		return;
	}
	time_--;
	if (time_ <= 0) {
		isFinished_ = true;
		fire_();
	}
}

// 完了フラグのゲッター
bool TimedCall::IsFinished() { return isFinished_; }

//残り時間のゲッター
uint32_t TimedCall::GetTimer() { return time_; }


