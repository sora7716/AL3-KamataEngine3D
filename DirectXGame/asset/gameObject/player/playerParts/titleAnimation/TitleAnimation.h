#pragma once
#include <Vector3.h>
#define oneLap std::numbers::pi_v<float> * 2.0f

//前方宣言
class Player;
class RailCamera;

/// <summary>
/// タイトルのアニメーション
/// </summary>
class TitleAnimation {
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleAnimation() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleAnimation() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="playerParts"></param>
	void Initialize(Player* player, RailCamera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="isHome">ホームかどうかのフラグ</param>
	void Update(bool isHome);

	/// <summary>
	/// ゲームスタート時のアニメーションを始めるかどうかのフラグ
	/// </summary>
	/// <param name="isGameStartAnimation"></param>
	void SetIsGameStartAnimation(bool isGameStartAnimation) { isGameStartAnimation_ = isGameStartAnimation; }

	/// <summary>
	/// ゲームシーンに遷移したかどうかのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsMoveGameScene() { return isMoveGameScene_; };

	/// <summary>
	/// ゲームシーンに変更フラグ
	/// </summary>
	/// <returns></returns>
	bool IsChangeGameScene() { return isChangeGameScene_; }

private: // メンバ関数
	/// <summary>
	/// 腕を回転させる
	/// </summary>
	void ArmRotate();

	/// <summary>
	/// 大きくなったり小さくなったりする
	/// </summary>
	void BigAndSmall();

	/// <summary>
	/// 見回す
	/// </summary>
	/// <param name="isStart">見回すのを始めるかどうかのフラグ</param>
	void LookAround(bool& isStart);

	/// <summary>
	/// 腕を落とす
	/// </summary>
	void ArmDrop();

	/// <summary>
	/// 下を見る
	/// </summary>
	void LookDown(bool& isLookDown, bool& isUndoLeft, bool& isUndoRight, bool& isLeftDrop);

	/// <summary>
	/// 下に落ちに行く
	/// </summary>
	void FallDown();

public:                                                // 静的メンバ変数
	static void (TitleAnimation::*animationTable[])(); // メンバ関数ポインタテーブル
	static inline const int kAnimationInterval = 1200; // アニメーションがスタートするまでの時間
	static inline const int kAnimationMaximumNumber = 3;

private: // メンバ変数
	Player* player_ = nullptr; // プレイヤー
	RailCamera* camera_ = nullptr;//カメラ
	int animationStartTimer_ = 0;//アニメーションを開始するまでのタイマー
	bool isAnimationStart_ = false;//アニメーションをスタートするかどうかのフラグ
	bool isAnimationEnd_ = false;//アニメーションが終了したかどうかのフラグ
	int animationNumber_ = 0;//アニメーションをする番号
	float animationFrame_ = 0.0f;//待機時間のアニメーションフレーム
	bool isGameStartAnimation_ = false;//ゲームがスタートするときのアニメーション
	bool isMoveGameScene_ = false;//ゲームシーンに遷移

	bool isCameraMove_ = true;//カメラの動くアニメーション
	bool isPlayerMove_ = false;//プレイヤーが動く
	bool isChangeGameScene_ = false;//ゲームシーンに変更
};
