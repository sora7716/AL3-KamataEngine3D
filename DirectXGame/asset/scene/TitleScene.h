#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "asset/gameObject/fade_image/Fade.h"
#include "asset/gameObject/titleFont/TitleFont.h"
#include "asset/create/Create.h"
#include "asset/gameObject/enemy/Enemy.h"
#include "asset/gameObject/pressSpace/GameStart.h"
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

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	bool finished_; // 終了フラグ
	Phase phase_ = Phase::kFadeIn;//現在のフェーズ
	ViewProjection viewProjection_;//ビュープロジェクション
	Fade* fade_ = nullptr; // フェード
	unique_ptr<Create> create_ = nullptr;//モデルクリエイト
	unique_ptr<TitleFont> titleFont_ = nullptr;//タイトルフォント
	unique_ptr<Enemy> enemy_[2];      // 敵
	unique_ptr<GameStart> pressSpace_ = nullptr;//ゲームスタートのボタン

public://メンバ関数
	static inline const float kFadeTime = 5;//フェードをしてほしい時間
};
