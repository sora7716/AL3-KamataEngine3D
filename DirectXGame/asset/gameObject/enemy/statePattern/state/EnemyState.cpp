#include "EnemyState.h"
#include "WorldTransform.h"
#include <numbers>

//止まっているときの初期化
void EnemyStay::Initialize() { status_ = Status::kStay; }

//止まっている状態から動く状態への変更
void EnemyStay::ChangePhase() { status_ = Status::kMove; }

//止まっている時
void EnemyStay::Exce(WorldTransform& worldTransform) { 
	(void)worldTransform;
	static int chageTime =120; //一秒間だけまつ
    if (chageTime > 0) {
		chageTime--;
	} else {
		ChangePhase();//状態を変更
	}
}

//動いているときの初期化
void EnemyMove::Initialize() { status_ = Status::kStay; }

//動いている状態から止まっている状態へ変更
void EnemyMove::ChangePhase() { status_ = Status::kMove; }

//動いているとき
void EnemyMove::Exce(WorldTransform& worldTransform) { 
	static float width = 2.0f; //振れ幅
	static float theta = 1.0f; // 角度
	worldTransform.translation_.x = width * std::sin(theta);//サイン波
	theta += std::numbers::pi_v<float> / 60.0f;//揺らすスピード
}
