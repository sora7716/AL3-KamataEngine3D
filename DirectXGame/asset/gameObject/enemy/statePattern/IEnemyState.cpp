#include "IEnemyState.h"
#include "WorldTransform.h"

// 弾を発射し、タイマーをリセットするコールバック関数
void IEnemyState::BulletTimeReset(WorldTransform& worldTransform,uint32_t timer) { 
	//弾を発射
	Fire(worldTransform);
	//発射タイマーをセットする
	timeCalls_.push_back(new TimedCall([this](WorldTransform& transform) { this->BulletTimeReset(transform, 60); }, timer));
}