#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "asset/gameObject/fade_image/Fade.h"

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
	/// タイトルフォントの更新処理
	/// </summary>
	void TitleFontUpdate();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	bool finished_; // 終了フラグ
	Phase phase_ = Phase::kFadeIn;//現在のフェーズ
	Model* titleFontModel_ = nullptr;//フォントのモデル
	WorldTransform titleFontWorldTransform_;//フォントのワールドトランスフォーム
	ViewProjection viewProjection_;//ビュープロジェクション
	uint32_t titleFontTextureHandle_ = 0u;//フォントのテクスチャ
	float theta_ = 0.0f;//角度
	float width_ = 0.0f;//振幅
	float positionY_ = 0.0f;//今のポジション
	Fade* fade_ = nullptr; // フェード
public://メンバ関数
	static inline const float kFadeTime = 5;//フェードをしてほしい時間
};
