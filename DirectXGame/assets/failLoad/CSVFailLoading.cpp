#include "CSVFailLoading.h"
#include <fstream>
using namespace std;

// 初期化
void CSVFailLoading::Initialize() { failDataCommands_ = LoadData("Resources/csvFail/enemyPop.csv"); }

// 更新
void CSVFailLoading::Update() { UpdatePopCommand(failDataCommands_, position_, phase_); }

//位置のゲッター
std::vector<Vector3> CSVFailLoading::GetPosition() {
	return position_; 
}

//ハイスコアのセーブ
void CSVFailLoading::HighScoreSave(int highScore) {
	std::string filePath = "HighScore_Save.csv";
	std::ofstream outFile(filePath);

	if (outFile.is_open()) {
		outFile << "Player HighScore, " << highScore << std::endl;
		outFile.close();
	}
}

void CSVFailLoading::UpdateScoreSave(std::string saveDateName, int& highScore) {

	std::stringstream saveData;
	// ファイルを開く
	std::ifstream file;
	file.open(saveDateName);
	// ファイルの内容を文字列ストリームにコピー
	saveData << file.rdbuf();
	file.close();
	// 1行分の文字列を入れる変数

	std::string line;
	// コマンドを実行ループ
	while (getline(saveData, line)) {
		if (line.empty()) {
			// 空白を飛ばす
			continue;
		}
		// 1行分の文字列をストリームに変換して解析し約する

		std::istringstream line_stream(line); // 読み込んだ行を文字列ストリームに変換
		std::string word;                     // 行から取り出した単語を格納する変数

		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("Player HighScore") == 0) {
			// x座標
			getline(line_stream, word, ',');
			highScore = atoi(word.c_str());
		}
	}
}

// フェーズのゲッター
vector<int32_t> CSVFailLoading::GetPhase() { return phase_; }

// 読み込み
std::stringstream CSVFailLoading::LoadData(std::string failName) {
	std::stringstream failDataCommands;
	// ファイルを開く
	std::ifstream file;
	file.open(failName);
	// ファイルの内容を文字列ストリームにコピー
	failDataCommands << file.rdbuf();
	file.close();

	return failDataCommands;
}

// コマンドの更新
void CSVFailLoading::UpdatePopCommand(stringstream& failDataCommands, vector<Vector3>& position, vector<int32_t>& phase) {
	// 1行分の文字列を入れる変数
	std::string line;
	// コマンドを実行ループ
	while (getline(failDataCommands, line)) {
		if (line.empty()) {
			// 空白を飛ばす
			continue;
		}
		// 1行分の文字列をストリームに変換して解析し約する

		std::istringstream line_stream(line); // 読み込んだ行を文字列ストリームに変換
		std::string word;                     // 行から取り出した単語を格納する変数

		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)atof(word.c_str());

			// 敵を発生させる
			Vector3 newPosition = {x, y, z};
			position.push_back(newPosition);
		} else if (word.find("PHASE") == 0) {
			getline(line_stream, word, ',');
			// 待ち時間
			int32_t newWaitTime = atoi(word.c_str());
			// 待機時間
			phase.push_back(newWaitTime); // どれくらい待機するか
		}
	}
}
