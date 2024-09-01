#include "EnemyState.h"
#include "Model.h"
#include "WorldTransform.h"
#include "asset/math/Math.h"


//デストラクタ
EnemeyApproach::~EnemeyApproach() { 

}

// 初期化
void EnemeyApproach::Initialize() {
	//接近に初期化
	phase_ = Phase::Approach;
	//firstPosition_ = position;//最初の位置を設定
}

// 状態を遷移(接近状態から)
void EnemeyApproach::ChangePhase() { phase_ = Phase::Leave; }

// 接近を実行
void EnemeyApproach::Exce(WorldTransform& worldTransform) {
	// 敵の動くスピード
	Vector3 velocity{0, 0, -kCharacterSpeed};
	// 移動(ベクトル加算)
	worldTransform.translation_ += velocity;
	// 規定の位置に到達したら離脱
	if (worldTransform.translation_.z < 0.0f) {
		ChangePhase();
	}
}

//初期化
void EnemeyLeave::Initialize() { 
	//firstPosition_ = position;//最初の位置を設定
}

// 状態を遷移(離脱状態から)
void EnemeyLeave::ChangePhase() { phase_ = Phase::Approach; }

// 離脱を実行
void EnemeyLeave::Exce(WorldTransform& worldTransform) {
	//フェーズがLeaveじゃなかった場合
	if (phase_ == Phase::phaseNum) {
		phase_ = Phase::Leave; 
	}
	// 敵の動くスピード
	Vector3 velocity{-kCharacterSpeed, kCharacterSpeed, -kCharacterSpeed};
	// 移動(ベクトル加算)
	worldTransform.translation_ += velocity;
	if (worldTransform.translation_.y > 100) {
		worldTransform.translation_ = firstPosition_;
		ChangePhase();
	}
}