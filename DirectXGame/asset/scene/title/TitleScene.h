#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "asset/gameObject/fade/Fade.h"
#include "asset/create/Create.h"
#include "asset/gameObject/player/Player.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/skydome/SkyDome.h"

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
	static inline const float kFadeTime = 5; // フェードをしてほしい時間

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	bool isDebugCameraActive_ = false;// デバックカメラをオンにするか
	unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	bool isFinished_; // 終了フラグ
	Phase phase_ = Phase::kFadeIn;//現在のフェーズ
	ViewProjection viewProjection_;//ビュープロジェクション
	unique_ptr<Fade> fade_ = nullptr;    // フェード
	unique_ptr<Create> create_ = nullptr;//モデルクリエイト
	unique_ptr<Player> player_ = nullptr;//プレイヤー
	unique_ptr<SkyDome> skyDome_ = nullptr; // 天球
	// レールカメラ
	unique_ptr<RailCamera> railCamera_ = nullptr;
	WorldTransform railCameraWorldTransform_;
};
