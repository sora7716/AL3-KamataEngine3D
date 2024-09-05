#include "EnemyState.h"
#include "asset/gameObject/enemy/Enemy.h"
#include <numbers>

// 止まっているときの初期化
void EnemyStay::Initialize() { status_ = Status::kStay; }

// 止まっている状態から動く状態への変更
void EnemyStay::ChangePhase() { status_ = Status::kMove; }

// 止まっている時
void EnemyStay::Exce(Enemy& enemy) {
	enemy.StatusStay(); // 止まる状態
	if (enemy.IsStatusChange()) {
		ChangePhase();                  // ステータスを変更
		enemy.SetIsStatusChange(false); // ステータス変更のフラグをfalseに設定
	}
}

// 動いているときの初期化
void EnemyLateralMove::Initialize() { status_ = Status::kMove; }

// 動いている状態から止まっている状態へ変更
void EnemyLateralMove::ChangePhase() { status_ = Status::kStay; }

// 動いているとき
void EnemyLateralMove::Exce(Enemy& enemy) {
	enemy.StatusLateralMove(); // 横移動の状態
	if (enemy.IsStatusChange()) {
		ChangePhase();                  // ステータスを変更
		enemy.SetIsStatusChange(false); // ステータス変更のフラグをfalseに設定
	}
}
