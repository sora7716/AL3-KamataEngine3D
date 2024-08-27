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
	//離脱に初期化
	phase_ = Phase::Leave; 
}

// 状態を遷移(離脱状態から)
void EnemeyLeave::ChangePhase() {}

// 離脱を実行
void EnemeyLeave::Exce(WorldTransform& worldTransform) {
	//フェーズがLeaveじゃなかった場合
	if (phase_ == Phase::phaseNum) {
		Initialize();//初期化する
	}
	// 敵の動くスピード
	//Vector3 velocity{-kCharacterSpeed, kCharacterSpeed, -kCharacterSpeed};
	Vector3 velocity{};
	// 移動(ベクトル加算)
	worldTransform.translation_ += velocity;
}