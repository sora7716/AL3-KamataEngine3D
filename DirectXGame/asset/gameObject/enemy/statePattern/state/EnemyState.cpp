#include "EnemyState.h"
#include "asset/gameObject/enemy/Enemy.h"
#include <numbers>

// 止まっているときの初期化
void EnemyStay::Initialize() { status_ = Status::kStay; }

// 止まっている状態から動く状態への変更
void EnemyStay::ChangePhase() { status_ = Status::kLateralMove; }

// 止まっている時
void EnemyStay::Exce(Enemy& enemy) {
	enemy.StatusStay(); // 止まる状態
}

// 横に動いているときの初期化
void EnemyLateralMove::Initialize() { status_ = Status::kLateralMove; }

// 横に動いている状態から止まっている状態へ変更
void EnemyLateralMove::ChangePhase() { status_ = Status::kStay; }

// 横に動いているとき
void EnemyLateralMove::Exce(Enemy& enemy) {
	enemy.StatusLateralMove(); // 横移動の状態
}

//縦に動いているときの初期化
void EnemyVerticalMove::Initialize() { status_ = Status::kVerticalMove; }

void EnemyVerticalMove::ChangePhase() {}

//縦に動いているとき
void EnemyVerticalMove::Exce(Enemy& enemy) { 
	//縦移動の状態
	enemy.StatusVerticalMove();
}
