#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "asset/create/Create.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/fade/Fade.h"
#include "asset/gameObject/player/Player.h"
#include "asset/gameObject/player/playerParts/titleAnimation/TitleAnimation.h"
#include "asset/gameObject/skydome/SkyDome.h"
#include "asset/gameObject/titleFont/TitleFont.h"
#include "asset/gameObject/titleFont/buttom/SelectButton.h"
#include "asset/scene/title/select/Select.h"

#include <memory>
using namespace std;

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene {
public: // 構造体など
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kAnimation,
		kFadeOut, // フェードアウト
	};

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了フラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool IsFinished() const;

	/// <summary>
	/// 終了フラグのセッター
	/// </summary>
	/// <param name="isFinished"></param>
	void SetIsFinished(const bool& isFinished);

	/// <summary>
	/// BGMを止める関数
	/// </summary>
	void BGMStop();

private: // メンバ変数
	/// <summary>
	/// 更新処理のフェーズの変更
	/// </summary>
	void ChangePhaseUpdate();

	/// <summary>
	/// デバックカメラの操作
	/// </summary>
	void DebugCameraMove();

	/// <summary>
	/// パーツの位置と角度のセッターをまとめた
	/// </summary>
	void SetPartisPositionAndAngle();

public: // メンバ関数
	static inline const float kFadeTime = 3; // フェードをしてほしい時間

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isDebugCameraActive_ = false;              // デバックカメラをオンにするか
	unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	bool isFinished_;               // 終了フラグ
	Phase phase_ = Phase::kFadeIn;  // 現在のフェーズ
	ViewProjection viewProjection_; // ビュープロジェクション
	// フェード
	unique_ptr<Fade> fade_ = nullptr;
	// モデルクリエイト
	unique_ptr<Create> create_ = nullptr;
	// プレイヤー
	unique_ptr<Player> player_ = nullptr;
	// 天球
	unique_ptr<SkyDome> skyDome_ = nullptr;
	// レールカメラ
	unique_ptr<RailCamera> railCamera_ = nullptr;
	WorldTransform railCameraWorldTransform_;
	// タイトルアニメーション
	unique_ptr<TitleAnimation> titleAnimation_ = nullptr;
	// セレクト画面
	unique_ptr<Select> selectScene_ = nullptr;
	// タイトルフォント
	unique_ptr<TitleFont> titleFont_ = nullptr;
	// セレクト画面で使用するボタン
	unique_ptr<ISelectButton> selectButtons_[ISelectButton::kButtonNum] = {nullptr};

	// BGM
	uint32_t soundDataHandle_ = 0; // BGM読み込む為のハンドル
	uint32_t soundPlayHandle_ = 0; // BGMを再生する為のハンドル
}
;
