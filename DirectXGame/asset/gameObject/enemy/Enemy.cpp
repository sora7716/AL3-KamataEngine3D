#include "Enemy.h"
#include <cassert>
#include "Model.h"
#include "ViewProjection.h"
using namespace std;
Enemy::~Enemy() { 
	
}
// 初期化
void Enemy::Initialize(Model* model, ViewProjection* viewProjection,Vector3 position) { 
	assert(model);//Nullチェック
	model_ = model;//モデルを受け取る
	viewProjection_ = viewProjection;//ビュープロジェクションを受け取る
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;//初期位置を設定
	//ステータスを設定
	actions_[0] = new EnemyStay();  // 止まっているとき
	actions_[1] = new EnemyMove();//動いて切るとき
	actions_[0]->Initialize();//初期化
	status_ = actions_[0]->GetStatus();//ステータスを得る
}
//敵のステータスのメンバ関数ポインタの初期化
void (IEnemyState::*IEnemyState::EnemyPhaseTable[])(WorldTransform&) = {
    static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemyStay::Exce),
    static_cast<void (IEnemyState::*)(WorldTransform&)>(&EnemyMove::Exce),
};

// 更新
void Enemy::Update() { 
	//現在のステータスの算出
	status_ = actions_[(int)status_]->GetStatus();
	//現在のステータスに上書き
	actions_[(int)status_]->SetStatus(status_);
	// 現在のフェーズを実行
	(actions_[status_]->*IEnemyState::EnemyPhaseTable[static_cast<size_t>(status_)])(worldTransform_);
	//行列の更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_);//
}
