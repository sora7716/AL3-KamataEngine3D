#pragma once
#include<cmath>
#define _USE_MATH_DEFINES
#include <sstream>
#include <list>
#include "Vector3.h"

/// <summary>
/// CSVファイルを読み込む
/// </summary>
class CSVFailLoading{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CSVFailLoading() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CSVFailLoading() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
    /// 位置のゲッター
    /// </summary>
	std::list<Vector3>GetPosition();

	/// <summary>
	/// ハイスコアのセーブ
	/// </summary>
	/// <param name="highScore">ハイスコア</param>
	static  void HighScoreSave(int highScore);

private: // メンバ変数

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="failName">csvファイルの名前</param>
	std::stringstream LoadData(std::string failName);

	/// <summary>
	/// コマンドの更新
	/// </summary>
	/// <param name="failDataCommands">コマンドを格納しておく変数</param>
	void UpdatePopCommand(std::stringstream& failDataCommands, std::list<Vector3>& position, int32_t waitTime);

private://メンバ変数
	std::stringstream failDataCommands_;//ファイルデータを格納しておく変数
	std::list<Vector3>position_;//データに書いてあった位置を格納しておく変数
	int32_t waitTime_ = 0;  // 待機時間のカウンタを保持するための変数
};

