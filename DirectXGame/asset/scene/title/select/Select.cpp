#include "Select.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/player/Player.h"
#include "input/Input.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG

// 初期化
void Select::Initialize(Player* player, RailCamera* camera) {
	// プレイヤーを受け取る
	player_ = player;
	// カメラを受け取る
	camera_ = camera;
	frame_ = 0.0f; // フレーム数を再設定
}

// 更新
void Select::Update(int phase) {
	Input* input = Input::GetInstance();
	if (phase != 2) {
		// マウスの左クリックでisMoveSelect_を切り替える
		if (input->TriggerKey(DIK_SPACE) && !isWasButtonPressed_) {
			isWasButtonPressed_ = true; // ボタンを押したかどうか
			isMoveSelect_ ^= true;      // 状態を反転
			frame_ = 0;                 // アニメーション用フレームをリセット
		} else if (isMoveSelect_ && input->TriggerKey(DIK_ESCAPE) && !isWasButtonPressed_) {
			isWasButtonPressed_ = true; // ボタンを押したかどうか
			isMoveSelect_ = false;      // 状態をfalse
			frame_ = 0;                 // アニメーション用フレームをリセット
		}
	}
	//ルールシーン遷移
	MoveRule();
	// カメラとプレイヤーを移動させる
	if (isWasButtonPressed_ ) {
		SelectScene();
	}

#ifdef _DEBUG
	ImGui::Begin("select");
	ImGui::Text("frame:%f", frame_);
	ImGui::Checkbox("isMoveSelect:", &isMoveSelect_);
	ImGui::Checkbox("isWasButtonPressed:", &isWasButtonPressed_);
	ImGui::Text("phase:%d", phase);
	ImGui::End();
#endif // _DEBUG
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
	} else if (!isMoveSelect_ && !isRuleSceneNow_) {                                                              // 元の位置に戻る
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
	}
}
