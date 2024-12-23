#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// <summary>
/// ログを書き込む
/// </summary>
class Log final {
public: // 列挙型
	// ログを書き込むときのタイプ
	enum class Levels { kInformation, kWarning, kError, kTypeNum };

public: // メンバ関数
	/// <summary>
	/// インスタンスのゲッター
	/// </summary>
	/// <returns></returns>
	static Log* GetInstance();

	/// <summary>
	/// ログファイルの生成または初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ログファイルにログを追加
	/// </summary>
	/// <param name="log">ログの内容</param>
	void AddLog(const std::string& log);

	// コピーコンストラクタを禁止
	Log(const Log& log) = delete;
	// 代入演算子を禁止
	const Log operator=(const Log& log) = delete;

private: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Log() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Log() = default;

	/// <summary>
	/// 現在の時間を知る
	/// </summary>
	std::string CheckTime();

	/// <summary>
	/// ログを書き込む
	/// </summary>
	/// <param name="outFile">Log.txt</param>
	/// <param name="logLevels">ログのレベル</param>
	/// <param name="log"></param>
	void WriteLog(std::ofstream& outFile, Levels logLevels, const std::string& log);

private: // メンバ変数
	// ファイルパス
	std::string filePath_ = "";
	// ログのタイプ
	std::vector<std::string> logType_;
};

// ログのレベル
using LogLevels = Log::Levels;