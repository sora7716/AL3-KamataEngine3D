#pragma once
#include "vector"

class ContactRecord {

public:

	// 履歴追加
	void AddRecord(int32_t number);

	// 履歴チェック
	bool CheckRecord(int32_t number);

	// 履歴抹消
	void Clear();

private:

	// 履歴
	std::vector<int32_t> history_;

};