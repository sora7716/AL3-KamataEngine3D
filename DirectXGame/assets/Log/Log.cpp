#include "Log.h"
#include <ctime>

// インスタンスのゲッター
Log* Log::GetInstance() {
	// 生成
	static Log instance;
	return &instance;
}

// ログファイルの生成または初期化
void Log::Initialize() {
	// ファイル名
	filePath_ = "Log.txt";
	// ログのタイプの初期化
	logType_.resize((int)LogLevels::kTypeNum);
	logType_ = {
	    "[情報]",
	    "[警告]",
	    "[エラー]",
	};
	// filePathと同じファイルを開く、存在しない場合は作成する
	std::ofstream outFile(filePath_);
	WriteLog(outFile, LogLevels::kInformation, "ログの書き込みを開始します");
}

// ログファイルにログを追加
void Log::AddLog(const std::string& log) {
	// ログファイルを開く(アペンドモード)
	std::ofstream outFile(filePath_, std::ios::app);

	// ログを書き込む
	if (outFile.is_open()) {
		outFile << log << std ::endl;
		outFile.close();
	}
}

// 現在の時間を知る
std::string Log::CheckTime() {
	std::time_t now = std::time(nullptr);
	char buf[80];
	// スレッドセーフな localtime_s を使用
	struct tm localTime;
	localtime_s(&localTime, &now);

	// フォーマット文字列を修正
	std::strftime(buf, sizeof(buf), "%y-%m-%d %H:%M:%S", &localTime);
	return std::string(buf);
}

// ログを書き込む
void Log::WriteLog(std::ofstream& outFile, LogLevels logLevels, const std::string& log) {
	// ログを書き込む
	if (outFile.is_open()) {
		outFile << CheckTime() << "-" << logType_[(int)logLevels] << log << std::endl;
		outFile.close();
	}
}
