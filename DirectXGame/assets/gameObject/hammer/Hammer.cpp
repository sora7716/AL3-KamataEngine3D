#include "assets/gameobject/hammer/Hammer.h"
#include "assets/gameobject/enemy/Enemy.h"
#include "cassert"
#ifdef _DEBUG
#include "imgui.h"
using namespace ImGui;
#endif // _DEBUG

void Hammer::Initialize(Model* model, ViewProjection* viewProjection) {

	
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 1.37f;
	worldTransform_.rotation_.x = 3;

	Collider::Initialize();

	Collider::SetTypeID(static_cast<uint32_t>(CollisionTypeIdDef::kPlayerWeapon));

	// objファイルを読み込む
	modelHitEffect_.reset(Model::CreateFromOBJ("effect", true));

	hitEffect_ = std::make_unique<HitEffect>();
	hitEffect_->Initialize(modelHitEffect_.get(), viewProjection_, GetCenterPosition());
		

}

void Hammer::Update() {

#ifdef _DEBUG
	Begin("hammer");
	DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	DragFloat3("translate", &worldTransform_.translation_.x, 0.01f);
	End();
#endif // DEBUG

	/*ヒットエフェクトの更新*/
	if (hitEffect_) {
		hitEffect_->Update();
	}


	/*ワールド変換データの行列更新*/
	worldTransform_.UpdateMatrix();
}

void Hammer::Draw() { 

	/*ヒットエフェクトの描画*/
	if (hitEffect_) {
		hitEffect_->Draw();
	}

	/*モデル(ハンマー)の描画*/
	model_->Draw(worldTransform_, *viewProjection_); 
}

void Hammer::OnCollision([[maybe_unused]] Collider* other) {
	// 衝突相手の種別IDを取得
	uint32_t typeID = other->GetTypeID();
	// 衝突相手が敵なら
	if (typeID == static_cast<uint32_t>(CollisionTypeIdDef::KEnemy)) {
		Enemy* enemy = static_cast<Enemy*>(other);
		int32_t serialNumber = enemy->GetSerialNumber();
		
		// 接触履歴があれば何もせずに抜ける
		if (contactRecord_.CheckRecord(serialNumber)) {
			return;
		}

		// 接触記録に登録する
		contactRecord_.AddRecord(serialNumber);

		
	}
}

void Hammer::ClearContactRecord() {
	// 接触履歴を抹消する
	contactRecord_.Clear();
}

Vector3 Hammer::GetCenterPosition() const {

	// ローカル座標でのオフセット
	const Vector3 offset = {0.f, 4.5f, 0.f};
	// ワールド座標に変換
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);
	return worldPos;
}

const Vector3& Hammer::GetRotation() const { return worldTransform_.rotation_; }

void Hammer::SetScale(const Vector3& scale) { worldTransform_.scale_ = scale; }

void Hammer::SetRotation(const Vector3& rotation) { worldTransform_.rotation_ = rotation; }

void Hammer::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }