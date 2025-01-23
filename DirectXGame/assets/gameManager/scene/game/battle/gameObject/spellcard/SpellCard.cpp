#include "SpellCard.h"
#include "cassert"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/collision/shape/obb/OBB.h"

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化処理
void SpellCard::Initialize(Model* model, ViewProjection* viewProjection) {
	// NULLチェック
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.z = 2.0f;

	wireFrame_ = std::make_unique<OBB>();
	wireFrame_->Initialize({.size = worldTransform_.scale_, .rotation = worldTransform_.rotation_, .center = GetWorldPos()},viewProjection);

	InitializeAnimation();
}

// 更新処理
void SpellCard::Update() {
#ifdef _DEBUG
	DebugText("SpellCard");
#endif // _DEBUG

	// スペルカード未取得時の処理
	SpellCard::Idol();
	worldTransform_.UpdateMatrix();
	wireFrame_->Update();
	wireFrame_->SetRotate(worldTransform_.rotation_);
	wireFrame_->SetPosition(worldTransform_.translation_);
}

// 描画処理
void SpellCard::Draw(uint32_t textureHandle) {

	if (isSpellCardGet_) {
		return;
	}
	model_->Draw(worldTransform_,*viewProjection_,textureHandle); 
}

// ワイヤーの描画
void SpellCard::DrawWire() {

	if (isSpellCardGet_) {
		return;
	}
	wireFrame_->Draw(); 
}

// 取得時の処理
void SpellCard::OnCollision() {
    Vector3 scaleSpeed = {0.01f, 0.01f, 0.01f};
	worldTransform_.scale_ -= scaleSpeed;

	float rotateSpeed = 0.5f;
	worldTransform_.translation_.y += rotateSpeed;

	if (worldTransform_.scale_.x < 0 && worldTransform_.scale_.y < 0 && worldTransform_.scale_.z < 0) {
		isSpellCardGet_ = true;
	}
}

// デバッグテキスト
void SpellCard::DebugText(const char* label) {
	(void)label;
#ifdef _DEBUG
	ImGui::Begin(label);
	ImGui::DragFloat3("scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::Checkbox("isGet", &isSpellCardGet_);
	ImGui::End();
#endif // _DEBUG
}

// ワールド座標の取得
Vector3 SpellCard::GetWorldPos() {
	return { worldTransform_.matWorld_.m[3][0], 
		     worldTransform_.matWorld_.m[3][1], 
		     worldTransform_.matWorld_.m[3][2]
	}; 
}

// ワイヤーフレームのGetter
OBB* SpellCard::GetWireFrame() { return wireFrame_.get(); }

// スペルカード取得のSetter
void SpellCard::SetIsSpellCardGet(bool isSpellCardGet) { isSpellCardGet_ = isSpellCardGet; }

// アニメーションの初期化
void SpellCard::InitializeAnimation() {
	floatingParameter_ = 0.0f;
	amplitube = 0.25f;
	cycle_ = 120;
	angleTimer_ = 0.0f;
}

float SpellCard::UpdateFloatingGimmick() {
	float result = {};
	const float step = 2.0f * pi_f / cycle_;
	floatingParameter_ += step;
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * pi_f);
	result = std::sin(floatingParameter_) * amplitube;
	return result;
}

// スペルカード未取得時の処理
void SpellCard::Idol() {
	
	if (isSpellCardGet_) {
		return;
	}

	const float rotateSpeed = 0.05f;
	worldTransform_.rotation_.y += rotateSpeed;

	worldTransform_.translation_.y = UpdateFloatingGimmick();
	
}

