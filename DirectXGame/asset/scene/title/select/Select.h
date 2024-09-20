#pragma once
#include "asset/math/Math.h"
#include "WorldTransform.h"

// 前方宣言
class RailCamera;
class Player;
class Model;
class ViewProjection;

/// <summary>
/// セレクト画面
/// </summary>
class Select {
public:  // メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Select()=default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Select() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="camera">カメラ</param>
	/// <param name="ruleMoji">ルールの文字</param>
	/// <param name="ruleBack">ルールの背景</param>
	void Initialize(Player*player,RailCamera*camera,Model*ruleMoji,Model*ruleBack,ViewProjection*viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(int phase);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ホームかどうかのフラグ
	/// </summary>
	/// <returns>isHome</returns>
	bool IsHome();

	/// <summary>
	/// セレクト画面への遷移フラグ
	/// <returns></returns>
	bool IsMoveSelect();

	/// <summary>
	/// フレームのゲッター
	/// </summary>
	/// <returns></returns>
	float GetFrame();

    /// <summary>
    /// ルールシーンへ遷移フラグのセッター
    /// </summary>
    /// <param name="isRuleScene"></param>
    void SetIsRuleScene(bool isRuleScene) { isRuleScene_ = isRuleScene; }

	/// <summary>
	/// 現在がルールシーンかどうかのフラグ
	/// </summary>
	/// <returns></returns>
	bool IsRuleSceneNow() { return isRuleSceneNow_; };

private:

	/// <summary>
	/// セレクト画面へ遷移
	/// </summary>
	void SelectScene();

	/// <summary>
	/// ルール画面
	/// </summary>
	void MoveRule();

public://静的メンバ変数

	static inline const float kEndFrame = 120.0f;//最大フレーム

private: // メンバ変数
	ViewProjection* viewProjection_ = nullptr;
	//カメラ
	RailCamera* camera_ = nullptr;
	//プレイヤー
	Player* player_ = nullptr;
	//セレクト画面に遷移フラグ
	bool isMoveSelect_ = false;
	//ゲームルール画面に遷移フラグ
	bool isMoveGemeRule_ = false;
	//ボタンを押したかどうかのフラグ
	bool isWasButtonPressed_ = false;
	//線形補間に使用するフレーム
	float frame_ = 0.0f;
	//元の画面にいるかどうか
	bool isHome_ = true;

	//ルールシーンへ遷移フラグ
	Model* ruleBackModel_ = nullptr;
	Model* ruleMojiModel_ = nullptr;
	WorldTransform ruleMojiWorldTransform_;
	WorldTransform ruleBackWorldTransform_;
	bool isRuleScene_ = false;//ルールシーンに遷移
	bool isRuleSceneNow_ = false;//現在がルールシーン
	bool isDrawRule_ = false;//ルールの描画
	bool isDrawRuleBack_ = false;//ルールを元に戻す
	float ruleFrame_ = 0.0f;//ルールシーンのフレーム
	float ruleBeginPosY = 11.0f;
	float ruleEndPosY = 0.0f;
	float playerBeginPosX = 0.0f;
	float playerEndPosX = 7.5f;
	float playerResultX = 0.0f;
};
