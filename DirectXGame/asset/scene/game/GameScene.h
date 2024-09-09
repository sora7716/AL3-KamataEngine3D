#pragma once
#define WHITE Vector4{1.0f,1.0f,1.0f,1.0f}
#define BLACK Vector4{0.0f,0.0f,0.0f,1.0f}
#define DARK_BROWN Vector4 { 0.259f, 0.075f, 0.086f }
#define oneFrame float(1.0f/60.0f)

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "asset/create/Create.h"
#include "asset/gameObject/player/Player.h"
#include "asset/gameObject/camera/RailCamera.h"
#include "asset/gameObject/player/command/ICommand.h"
#include "asset/gameObject/player/command/InputHandler.h"
#include "asset/gameObject/enemy/Enemy.h"
#include "asset/gameObject/skydome/SkyDome.h"
#include "asset/gameObject/fade/Fade.h"
#include "asset/gameObject/score/Score.h"
#include "asset/failLoad/CSVFailLoading.h"
#include "asset/gameObject/hp/Hp.h"
#include "asset/gameObject/warp/Warp.h"

#include <memory>
using namespace std;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
public://列挙型

	//フィールドの状態
	enum class FieldStatus {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	// ゲームのフェーズ
	enum class GamePhase {
		kStart,
		kMain,
		kEnd,
	};

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	/// <returns>終了フラグ</returns>
	bool IsFinished();

	/// <summary>
	/// 終了フラグのセッター
	/// </summary>
	/// <param name="isFinished">終了フラグ</param>
	void SetIsFinished(bool isFinished);

private://メンバ関数

	/// <summary>
	/// デバックカメラ
	/// </summary>
	void DebugCameraMove();

	/// <summary>
	/// コマンドを受け取る
	/// </summary>
	void InputCommand();

	/// <summary>
	/// コマンドの更新
	/// </summary>
	void UpdateCommand();

	/// <summary>
	/// 衝突判定
	/// </summary>
	void CheackOnCollision();

	/// <summary>
	/// フィールドの更新
	/// </summary>
	void UpdateField();

	/// <summary>
	/// パーツの位置と角度のセッターをまとめた
	/// </summary>
	void SetPartisPositionAndAngle();

public://静的メンバ変数

	static inline const float kFieldChangeFadeTime = 1.0f;//フィールをフェードする時間
	static inline const float kScoreSource = 1.0f;//スコアの元
	static inline const int kEnemyBeginNum = 4;//障害物の最初にある数

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	ViewProjection viewProjection_;                 // ビュープロジェクション
	bool isDebugCameraActive_ = false;              // デバックカメラをオンにするか
	unique_ptr<DebugCamera> debugCamera_ = nullptr; // デバックカメラ
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//クリエイトクラス
	unique_ptr<Create> create_ = nullptr;
	//プレイヤークラス
	unique_ptr<Player> player_ = nullptr;
	//レールカメラ
	unique_ptr<RailCamera> railCamera_ = nullptr;
	WorldTransform railCameraWorldTransform_;
	//コマンド
	ICommand * lateralMovement_ = nullptr;//横移動
	ICommand * verticalMvement_ = nullptr;//縦移動
	//インプットハンドラ
	unique_ptr<InputHandler> inputHandler_ = nullptr;
	//障害物
	vector<Enemy*> enemis_;
	unique_ptr<IPlayerParts> playerParts_[IPlayerParts::PartsNum] = {nullptr};
	// CSVファイルロード
	unique_ptr<CSVFailLoading> enemyPopCommand_ = nullptr;
	//天球
	unique_ptr<SkyDome> skyDome_ = nullptr;
	bool isSkyDive_ = true;
	Vector4 fieldFadeColor_ = WHITE;
	//フェードスプライト(フィールドを変更)
	unique_ptr<Fade> fieldChangeFade_ = nullptr;
	float fadeTime_ = kFieldChangeFadeTime;//フェードする時間
	//フィールドの状態
	FieldStatus fieldStatus_ = FieldStatus::kMain;
	//スコア
	unique_ptr<Score> bitmapFont_ = nullptr;
	float score_ = 0;//現在のスコア
	//終了フラグ
	bool isFinished_ = false;
	//ゲームのフェーズ
	GamePhase gamePhase_ = GamePhase::kStart;
	//残機
	unique_ptr<Hp> playerHp_ = nullptr;
	//ワープポイント
	unique_ptr<Warp> warp_ = nullptr;
};
