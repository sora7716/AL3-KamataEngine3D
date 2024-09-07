#pragma once
#include <Vector3.h>

//前方宣言
class Player;

/// <summary>
/// タイトルのアニメーション
/// </summary>
class TitleAnimation {
public://メンバ関数

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
	void Initialize(Player* player);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

private://メンバ関数

	/// <summary>
	/// 腕を回転させる
	/// </summary>
	void ArmRotate();

public://静的メンバ変数

	static void (TitleAnimation::*animationTable[])();//メンバ関数ポインタテーブル
	static inline const int kAnimationInterval = 60;//アニメーションがスタートするまでの時間

private://メンバ変数
	Player* player_ = nullptr;//プレイヤー
	int animationStartTimer = 0;//アニメーションを開始するまでのタイマー
	bool isAnimationStart = false;//アニメーションをスタートするかどうかのフラグ
	bool isAnimationEnd = false;//アニメーションが終了したかどうかのフラグ
};
