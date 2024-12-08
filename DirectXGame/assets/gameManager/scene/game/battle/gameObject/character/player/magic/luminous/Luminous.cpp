#include "Luminous.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "ViewProjection.h"
#include "assets/math/Math.h"
#include "cassert"
#include "cstdlib"
#include "ctime"
#include "input/Input.h"

//float型でもrand使えるようにした
float RandomFloat(float min, float max) {
	// 0.0から1.0の範囲の乱数を生成
	float randFloat = static_cast<float>(rand()) / RAND_MAX;
	// minからmaxの範囲にスケーリング
	return min + randFloat * (max - min);
}
// 初期化
void Luminous::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	center_.Initialize();
	center_.translation_.y = 3.0f;
	std::srand(static_cast<uint32_t>(std::time(nullptr)));
	center_.scale_ = {0.8f, 0.8f, 0.8f};
	for (int i = 0; i < kEffectNum; i++) {
		// 位置
		WorldTransform* worldTranform = new WorldTransform;
		worldTranform->Initialize();
		worldTranform->translation_.y = 3.0f;
		worldTranform->scale_ = {kEffectSize, kEffectSize, kEffectSize};
		effects_.push_back(worldTranform);
		// 色
		ObjectColor* objectColor = new ObjectColor;
		objectColor->Initialize();
		Vector4 color = Math::ColorCodeTransform("#0FDE2B");
		effectColors_.push_back(color);
		objectColor->SetColor(color);
		effectsObjectColor_.push_back(*objectColor);
		//周期を設定
		moitionTime_.push_back(RandomFloat(0.1f, 3.0f));
	}
}

// 更新
void Luminous::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_W)) {
		move_.z = 1.0f;
		// 移動量に速さを反映
		move_ = Math::Normalize(move_) * kSpeed;
		Matrix4x4 rotMat = Math::MakeRotateXYZMatrix(directionViewProjection_->rotation_);
		move_ = Math::TransformNormal(move_, rotMat);
	}
	//エフェクトの動き
	Effect();
	//色のブレンド
	Blend();

	center_.translation_ += move_;
	center_.UpdateMatrix();
	for (auto& worldTransform : effects_) {
		// 行列の更新
		worldTransform->UpdateMatrix();
	}
}

void Luminous::DebugText() {
#ifdef DEBUG
	ImGui::Begin("luminous");
	ImGui::DragFloat3("scale", &center_.scale_.x, 0.1f);
	ImGui::DragFloat3("translation", &center_.translation_.x, 0.1f);
	ImGui::Text("effectColor:%f", effectColors_[0].w);
	ImGui::End();

#endif // DEBUG
}

// 描画
void Luminous::Draw() {
	model_->Draw(center_, *viewProjection_);
	for (int i = 0; i < effects_.size(); i++) {
		model_->Draw(*effects_[i], *viewProjection_, &effectsObjectColor_[i]);
	}
}

// 飛んでいく方向のビュープロジェクションのセッター
void Luminous::SetDirectionView(ViewProjection* viewProjection) { directionViewProjection_ = viewProjection; }

// エフェクト
void Luminous::Effect() {
	theta_[0] += deltaTime;
	theta_[1] -= deltaTime;
	// theta_[0] と theta_[1] を配列として扱う
	for (int i = 0; i < 2; ++i) { // i = 0はtheta_[0]、i = 1はtheta_[1]
		float theta = theta_[i];

		// LissajousCurveに渡す係数セット
		std::array<Vector3, 3> factors = {
		    {{3.0f * theta, 4.0f * theta, theta}, {3.0f * theta, theta, 4.0f * theta}, {theta, 4.0f * theta, 3.0f * theta}}
        };

		// カラー成分（最後の引数）
		std::array<Vector3, 3> colors = {
		    {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}}
        };

		// 各要素を処理
		for (int j = 0; j < 3; ++j) {
			int index = i * 3 + j; // 配列のインデックスを計算
			effects_[index]->translation_ = Math::LissajousCurve(factors[j], center_.translation_, colors[j]);
		}
	}
}

//色のブレンド
void Luminous::Blend() {
	changeAlphaTimer_ += deltaTime * 3.0f;
	// 色の変更
	for (int i = 0; i < effects_.size(); i++) {
		effectColors_[i].w = Math::Lerp(40, 10, EasingMode::kNormal, moitionTime_[i], changeAlphaTimer_);
		effectsObjectColor_[i].SetColor(effectColors_[i]);
		effectsObjectColor_[i].TransferMatrix();
	}
}
