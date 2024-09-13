#include "Select.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/player/Player.h"
#include "Model.h"
#include "ViewProjection.h"
#include "input/Input.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void Select::Initialize(Player* player, RailCamera* camera, Model* ruleMoji, Model* ruleBack,ViewProjection *viewProjection) {
	// プレイヤーを受け取る
	player_ = player;
	// カメラを受け取る
	camera_ = camera;
	frame_ = 0.0f; // フレーム数を再設定
	ruleMojiModel_ = ruleMoji;
	ruleBackModel_ = ruleBack;
	ruleBackWorldTransform_.Initialize();
	ruleMojiWorldTransform_.Initialize();
	ruleBackWorldTransform_.parent_ = &camera_->GetWorldTransform();
	ruleMojiWorldTransform_.parent_ = &ruleBackWorldTransform_;
	ruleBackWorldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	ruleBackWorldTransform_.translation_.z = 12.0f;
	ruleBackWorldTransform_.translation_.y = 11.0f;
	viewProjection_ = viewProjection;
}

// 更新
void Select::Update(int phase) {
	Input* input = Input::GetInstance();
	if (phase != 2) {
		if (!isRuleSceneNow_) {
			// マウスの左クリックでisMoveSelect_を切り替える
			if (input->TriggerKey(DIK_SPACE) && !isWasButtonPressed_) {
				isWasButtonPressed_ = true; // ボタンを押したかどうか
				isMoveSelect_ ^= true;      // 状態を反転
				frame_ = 0;                 // アニメーション用フレームをリセット
			}
		} else if (input->TriggerKey(DIK_ESCAPE)) {
			isWasButtonPressed_ = true; // ボタンを押したかどうか
			isMoveSelect_ = false;
			isRuleSceneNow_ = false;
			frame_ = 0.0f;
		}
		if (isMoveSelect_ && input->TriggerKey(DIK_ESCAPE) && !isWasButtonPressed_) {
			isWasButtonPressed_ = true; // ボタンを押したかどうか
			isMoveSelect_ = false;      // 状態をfalse
			frame_ = 0;                 // アニメーション用フレームをリセット
		}
	}
	// ルールシーン遷移
	MoveRule();
	// カメラとプレイヤーを移動させる
	if (isWasButtonPressed_) {
		SelectScene();
	}

#ifdef _DEBUG
	ImGui::Begin("select");
	ImGui::Text("frame:%f", frame_);
	ImGui::Checkbox("isMoveSelect:", &isMoveSelect_);
	ImGui::Checkbox("isWasButtonPressed:", &isWasButtonPressed_);
	ImGui::Text("phase:%d", phase);
	ImGui::End();

	ImGui::Begin("opeMoji");
	ImGui::DragFloat3("rotation", &ruleMojiWorldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translaiton", &ruleMojiWorldTransform_.translation_.x, 0.1f);
	ImGui::End();

	ImGui::Begin("opeBack");
	ImGui::DragFloat3("rotation", &ruleBackWorldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("translaiton", &ruleBackWorldTransform_.translation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	ruleBackWorldTransform_.UpdateMatrix();
	ruleMojiWorldTransform_.UpdateMatrix();
}

void Select::Draw() {
	ruleBackModel_->Draw(ruleBackWorldTransform_, *viewProjection_);
	ruleMojiModel_->Draw(ruleMojiWorldTransform_, *viewProjection_);
}

// ホームかどうかのフラグ
bool Select::IsHome() { return isHome_; }

// セレクト画面への遷移フラグ
bool Select::IsMoveSelect() { return isMoveSelect_; }

// フレームのゲッター
float Select::GetFrame() { return frame_; }

// セレクト画面へ遷移
void Select::SelectScene() {
	// カメラ
	static Vector3 cameraBegin = camera_->GetWorldTransform().translation_; // カメラの初期位置
	Vector3 cameraEnd = {-3.0f, 0.0f, 10.0f};                               // カメラの移動する先
	static Vector3 cameraResult = {};                                       // カメラの位置の現在の結果を格納
	// プレイヤー
	static float playerAngleBeginY = player_->GetWorldTransform().rotation_.y; // プレイヤーの初期の角度
	float playerAngleEndY = -1.2f;                                             // プレイヤーの最終的な角度
	static float playerAngleResultY = 0.0f;                                    // プレイヤーの現在の角度を格納

	// アニメーションの進行度を管理
	if (frame_++ > kEndFrame) {
		frame_ = kEndFrame;          // フレームで固定
		isWasButtonPressed_ = false; // ボタンを押したかどうかのフラグをリセット
		// ホームかどうか
		if (isMoveSelect_) {
			isHome_ = false;
		} else if (!isMoveSelect_) {
			isHome_ = true;
		}
	}

	// カメラとプレイヤーの位置と回転の補間
	if (isMoveSelect_) {                                                                                         // 動かす
		cameraResult = Math::Lerp(cameraBegin, cameraEnd, Easing::InOutCirc(frame_ / kEndFrame));                // カメラの位置を線形補間する
		playerAngleResultY = Math::Lerp(playerAngleBeginY, playerAngleEndY, Easing::InSine(frame_ / kEndFrame)); // プレイヤーの角度を線形補間する
	} else if (!isMoveSelect_ && !isRuleSceneNow_) {                                                             // 元の位置に戻る
		cameraResult = Math::Lerp(cameraEnd, cameraBegin, Easing::InOutCirc(frame_ / kEndFrame));                // カメラの位置を線形補間する
		playerAngleResultY = Math::Lerp(playerAngleEndY, playerAngleBeginY, Easing::InSine(frame_ / kEndFrame)); // プレイヤーの角度を線形補間する
	}

	// カメラとプレイヤーの更新
	camera_->SetTranslation(cameraResult);                  // resultをセット
	player_->SetRotation({0.0f, playerAngleResultY, 0.0f}); // resultをセット
}

// ゲームルール
void Select::MoveRule() {
	if (isRuleScene_) {
		isRuleSceneNow_ = true;
		isDrawRule_ = true;
	}
	if (isDrawRule_) {
		if (ruleFrame_++ > kEndFrame) {
			ruleFrame_ = kEndFrame;
			isDrawRule_ = false;
			isDrawRuleBack_ = true;
		}
	} else if (isDrawRuleBack_&&!isRuleSceneNow_) {
		if (ruleFrame_-- < 0.0f) {
			ruleFrame_ = 0.0f;
			isDrawRuleBack_ = false;
		}
	}
	ruleBackWorldTransform_.translation_.y = Math::Lerp(ruleBeginPosY, ruleEndPosY, Easing::InOutBack(ruleFrame_ / kEndFrame));
	playerResultX = Math::Lerp(playerBeginPosX, playerEndPosX, Easing::InOutSine(ruleFrame_ / kEndFrame));
	player_->SetPosition({playerResultX, player_->GetWorldTransform().translation_.y, player_->GetWorldTransform().translation_.z});
#ifdef _DEBUG
	ImGui::Begin("RuleScene");
	ImGui::Checkbox("isRuleScene_", &isRuleScene_);
	ImGui::End();
#endif // _DEBUG
}
