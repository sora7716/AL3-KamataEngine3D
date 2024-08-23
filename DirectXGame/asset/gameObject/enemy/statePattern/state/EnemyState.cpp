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
	// 弾のモデルを生成
	bulletModel_ = Model::Create();
	// 発射タイマーを初期化
	fireTimer_ = kFireInterval;
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
	//発射タイマーカウントダウン
	fireTimer_--;
	//指定時間に達した
	if (fireTimer_ <= 0) {
		// 弾を発射
		Fire(worldTransform);
		//発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}

	// デスフラグが立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
		}
		return false;
	});
}

// 攻撃
void EnemeyApproach::Fire(WorldTransform& worldTransform) {

	// 弾の速度
	Vector3 velocity(0, 0, -kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = Math::TransformNormal(velocity, worldTransform.matWorld_);

	// 弾を生成
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(bulletModel_, worldTransform.translation_, velocity);

	// 弾を登録
	bullets_.push_back(newBullet);
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
	Vector3 velocity{-kCharacterSpeed, kCharacterSpeed, -kCharacterSpeed};
	// 移動(ベクトル加算)
	worldTransform.translation_ += velocity;
}

// 攻撃
void EnemeyLeave::Fire(WorldTransform& worldTransform) { (void)worldTransform; }
