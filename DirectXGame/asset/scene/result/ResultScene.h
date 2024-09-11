#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "asset/gameObject/fade/Fade.h"
#include "asset/gameObject/score/Score.h"

#include <memory>
using namespace std;

/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene {

public:

	enum class ResultState {
		kFadeIn,
		kMain,
		kFadeOut,
	};

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	ResultScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
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

	void SetScore(int score) { gameScore_ = score; }

	static inline const float kFadeTimer = 3;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// リザルトシーン用
	/// </summary>
	
	bool isFinished_ = false;

	ResultState phase_ = ResultState::kMain;

	unique_ptr<Score> score_;
	unique_ptr<Fade> fade_;
	int gameScore_ = 0000000;

};
