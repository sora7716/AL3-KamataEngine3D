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
#include "asset/create/Create.h"
#include "asset/gameObject/skydome/SkyDome.h"

#include <memory>
using namespace std;

class SceneText;

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

	void EaseMove();

	void EaseMoveOut();

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

	/// <summary>
	/// BGMを止める関数
	/// </summary>
	void BGMStop();

	static inline const float kFadeTimer = 3;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// リザルトシーン用
	/// </summary>
	
	bool isFinished_ = false;

	ResultState phase_ = ResultState::kFadeIn;

	unique_ptr<Score> score_ = nullptr;
	unique_ptr<Fade> fade_ = nullptr;
	int gameScore_ = 0000000;

	unique_ptr<Create> create_  = nullptr;

	ViewProjection viewProjection_;
	WorldTransform worldTransform_;
	unique_ptr<SkyDome> skyDome_ = nullptr;

	float frame[2] = {0, 0};
	float endFrame[2] = {120, 100};

	unique_ptr<SceneText> sceneText_ = nullptr;

	// BGM
	uint32_t soundDataHandle_ = 0; // BGM読み込む為のハンドル
	uint32_t soundPlayHandle_ = 0; // BGMを再生する為のハンドル
};
